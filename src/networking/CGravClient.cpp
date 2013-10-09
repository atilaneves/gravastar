#include "CGravClient.hpp"
#include "CMeleeClientStarter.hpp"
#include "CVersusMenu.hpp"
#include "network_buffers.hpp"
#include "stl_utils.hpp"
#include <thread>


static std::vector<unsigned char> portToBytes(uint16_t port) {
    const auto str = std::string("UdpPort ") + std::to_string(port);
    std::vector<unsigned char> vec;
    for(char c: str) vec.push_back(static_cast<unsigned char>(c));
    return vec;
}


CGravClient::CGravClient(const std::string& addr, int port):
    mTcpClient(addr, port),
    mServerUdpPort(rand() % 40000 + 10000) {

    mTcpClient.BlockingConnect();

    mTcpClient.Send(portToBytes(mServerUdpPort));
}


void CGravClient::Run(CRootMenu& rootMenu, CVersusMenu& versusMenu) {
    std::thread meleeThread;
    CMeleeClientStarter meleeStarter{rootMenu, mServerUdpPort};
    std::atomic_bool meleeRunning{true};
    mTcpClient.ReadUntil(meleeRunning, [&](const CTcpClient::MsgBuf& buf, size_t len) {
        auto tokens = msgBufToDeque(buf, len);
        const auto command = popFront(tokens);

        if(command == "Start") {
            std::cout << "Starting the melee" << std::endl;
            //tokens gets modified, so no ref capture
            meleeThread = std::thread([&, tokens] {
                    meleeStarter.Start(tokens, versusMenu.GetClientOptions());
            });
        } else if(command == "Stop")  {
            const auto winner = std::stoi(popFront(tokens));
            std::cout << "Stopping the melee. Winner: " << winner << std::endl;
            meleeStarter.Stop(winner);
            meleeRunning = false;
            meleeThread.join();
            return; //exits the lambda
        }
    });

    mTcpClient.Stop();
}
