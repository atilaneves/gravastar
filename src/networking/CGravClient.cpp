#include "CGravClient.hpp"
#include "CSongPlayer.hpp"
#include "network_buffers.hpp"
#include "output.hpp"
#include "stl_utils.hpp"
#include "Decerealiser.hpp"
#include <thread>


static std::vector<unsigned char> portToBytes(uint16_t port) {
    const auto str = std::string("UdpPort ") + std::to_string(port);
    std::vector<unsigned char> vec;
    for(char c: str) vec.push_back(static_cast<unsigned char>(c));
    return vec;
}


CGravClient::CGravClient(const std::string& addr, int port):
    mTcpClient(addr, port),
    mUdpReceiver(*this)
{
    mTcpClient.BlockingConnect();
    mTcpClient.Send(portToBytes(mUdpReceiver.GetPort()));
}


void CGravClient::Run(CSongPlayer& songPlayer, const CClientOptions& vsClientOptions) {
    std::thread meleeThread;
    std::atomic_bool meleeRunning{true};

    mTcpClient.ReadUntil(meleeRunning, [&](const CTcpClient::MsgBuf& buf, size_t len) {
        auto tokens = msgBufToDeque(buf, len);
        const auto command = popFront(tokens);

        if(command == "Start") {
            std::cout << "Starting the melee" << std::endl;
            //tokens gets modified, so no ref capture
            meleeThread = std::thread([&, tokens] {
                    StartMeleeClient(songPlayer, tokens, vsClientOptions);
            });
        } else if(command == "Stop")  {
            const auto winner = std::stoi(popFront(tokens));
            std::cout << "Stopping the melee. Winner: " << winner << std::endl;
            StopMeleeClient(winner);
            meleeRunning = false;
            meleeThread.join();
            return; //exits the lambda
        } else {
            std::cerr << "Unknown command in CGravClient::Run" << std::endl;
            assert(false);
        }
    });

    mTcpClient.Stop();
}

void CGravClient::StartMeleeClient(CSongPlayer& songPlayer, std::deque<std::string> options,
                                   const CClientOptions& vsClientOptions) {
    songPlayer.StopSong();
    CSound sound("meleeStart");
    sound.PlayCentre();

    const unsigned pilotIndex = std::stoi(popFront(options));
    mClientSocket.reset(new CClientSocket{pilotIndex});
    std::thread clientSocketThread{[&](){ mUdpReceiver.Run(); }};

    printCentre("Loading...");
    mMelee.reset(new CMeleeClient{GetGravOptions(options, vsClientOptions),
                                  *mClientSocket});
    mMelee->Run();

    mUdpReceiver.Stop();
    clientSocketThread.join();

    songPlayer.PlaySong();
}

void CGravClient::StopMeleeClient(int winner) {
    mMelee->Stop(winner);
}

CGravOptions CGravClient::GetGravOptions(std::deque<std::string>& options,
                                         const CClientOptions& vsClientOptions) const {
    const auto levelNb  = std::stoi(popFront(options));
    const auto nbPilots = std::stoi(popFront(options));
    const auto nbShips  = std::stoi(popFront(options));

    std::vector<CPilotOptions> allPilotOpts;
    for(int i = 0; i < nbPilots; ++i) {
        const auto name = popFront(options);
        const auto type = popFront(options);
        const auto& team = CTeam::FindByName(popFront(options));
        std::vector<std::string> ships;
        for(int j = 0; j < nbShips; ++j) {
            ships.push_back(popFront(options));
        }

        const CPilotInputOptions pilotInputOpts{"", 0, 0, 0, 0, 0, 0, 0, 0};
        allPilotOpts.emplace_back(name, type, team, ships, pilotInputOpts);
    }

    const auto meleeType = "Client";
    const auto powerupRate = 0.0f;
    const CMeleeOptions meleeOptions{meleeType, levelNb, powerupRate};

    const CClientOptions clientOptions{allPilotOpts, vsClientOptions};
    return {meleeOptions, clientOptions};
}

void CGravClient::UdpReceived(const boost::system::error_code& error,
                              size_t numBytes, const Array& bytes) {
    if(error && error != boost::asio::error::message_size) {
        std::cerr << "Error in CGravClient::AfterReceive" << std::endl;
        return;
    }

    Decerealiser cereal{bytes};
    mClientSocket->UpdateFrame(cereal);
}
