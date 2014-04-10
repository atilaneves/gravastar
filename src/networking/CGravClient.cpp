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
    mUdpSender(addr, port),
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
            //tokens gets modified, so no ref capture
            meleeThread = std::thread([&, tokens] {
                    StartMeleeClient(songPlayer, tokens, vsClientOptions);
            });
        } else if(command == "Stop")  {
            const auto winner = std::stoi(popFront(tokens));
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

static CGravOptions getGravOptions(std::deque<std::string>& serverOptions,
                                   const CClientOptions& vsClientOptions)  {
    const auto levelNb  = std::stoi(popFront(serverOptions));
    const auto nbPilots = std::stoi(popFront(serverOptions));
    const auto nbShips  = std::stoi(popFront(serverOptions));

    std::vector<CPilotOptions> allPilotOpts;
    for(int i = 0; i < nbPilots; ++i) {
        const auto name = popFront(serverOptions);
        const auto type = popFront(serverOptions);
        const auto& team = CTeam::FindByName(popFront(serverOptions));
        std::vector<std::string> ships;
        for(int j = 0; j < nbShips; ++j) {
            ships.push_back(popFront(serverOptions));
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

void CGravClient::StartMeleeClient(CSongPlayer& songPlayer,
                                   std::deque<std::string> serverOptions,
                                   const CClientOptions& vsClientOptions) {
    songPlayer.StopSong();
    CSound{"meleeStart"}.PlayCentre();

    const unsigned pilotIndex = std::stoi(popFront(serverOptions));
    mClientSocket.reset(new CClientSocket{pilotIndex, mUdpSender});

    printCentre("Loading...");
    mMelee.reset(new CMeleeClient{getGravOptions(serverOptions, vsClientOptions),
                                  *mClientSocket});
    mMelee->Run();

    songPlayer.PlaySong();
}

void CGravClient::StopMeleeClient(int winner) {
    mMelee->Stop(winner);
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
