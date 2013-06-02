#include "CClientMenu.hpp"
#include "CGravUpdateServer.hpp"
#include "CCanvas.hpp"
#include "CFont.hpp"
#include "CGravMenu.hpp"
#include "CVersusMenu.hpp"
#include "CMeleeClient.hpp"
#include "CTcpClient.hpp"
#include "CMeleeClientStarter.hpp"
#include "fontsdat.h"
#include "network_buffers.hpp"
#include <thread>
#include <algorithm>
#include <boost/asio.hpp>
#include <cstdlib>


CClientMenu::CClientMenu(const CSprite *cursorSprite, CGravMenu& gravMenu):
    CCursorMenu<CStringMenu>(cursorSprite, "Client"),
    mVersusMenu(gravMenu.GetVersusMenu()),
    mFont(MetroStyleExtendedBoldItalic28) {

}


std::string nextOption(std::deque<std::string>& strings) {
    auto str = strings.front();
    strings.pop_front();
    return str;
}

static std::vector<unsigned char> portToBytes(uint16_t port) {
    const auto str = std::string("UdpPort ") + std::to_string(port);
    std::vector<unsigned char> vec;
    for(char c: str) vec.push_back(static_cast<unsigned char>(c));
    return vec;
}

void CClientMenu::Run(CRootMenu &rootMenu) {
    PrintCentre("Connecting to server...");
    CTcpClient tcpClient("127.0.0.1", 12346);
    tcpClient.BlockingConnect();

    const uint16_t serverUdpPort = rand() % 40000 + 10000;
    std::cout << "Port is " << serverUdpPort << std::endl;
    tcpClient.Send(portToBytes(serverUdpPort));

    PrintCentre("Waiting for server...");
    std::thread meleeThread;
    CMeleeClientStarter meleeStarter{rootMenu, *this, serverUdpPort};
    std::atomic_bool meleeRunning{true};
    tcpClient.ReadUntil(meleeRunning, [&](const CTcpClient::MsgBuf& buf, size_t len) {
        auto tokens = msgBufToDeque(buf, len);
        const auto command = nextOption(tokens);

        if(command == "Start") {
            std::cout << "Starting the melee" << std::endl;
            //tokens gets modified, so no ref capture
            meleeThread = std::thread([&, tokens] {
                    meleeStarter.Start(tokens, mVersusMenu.GetClientOptions());
            });
        } else if(command == "Stop")  {
            const auto winner = std::stoi(nextOption(tokens));
            std::cout << "Stopping the melee. Winner: " << winner << std::endl;
            meleeStarter.Stop(winner);
            meleeRunning = false;
            meleeThread.join();
            return; //exits the lambda
        }
    });

    tcpClient.Stop();
}


void CClientMenu::PrintCentre(const std::string& str) const {
    CCanvas screenCanvas(screen);
    screenCanvas.Clear();
    mFont.PrintCentre(screenCanvas, screenCanvas.GetWidth()/2,
                      screenCanvas.GetHeight()/2, makecol(255, 255, 255), -1,
                      str);
}
