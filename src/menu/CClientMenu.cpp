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
#include <thread>
#include <algorithm>
#include <boost/asio.hpp>


CClientMenu::CClientMenu(const CSprite *cursorSprite, CGravMenu& gravMenu):
    CCursorMenu<CStringMenu>(cursorSprite, "Client"),
    mVersusMenu(gravMenu.GetVersusMenu()),
    mFont(MetroStyleExtendedBoldItalic28) {

}

static std::vector<std::string> msgBufToVec(const CTcpClient::MsgBuf& buf, size_t len) {
    std::string bufStr{buf.cbegin(), buf.cbegin() + len};
    std::cout << "Read " << len << " bytes: " << bufStr << std::endl;
    std::istringstream stream{bufStr};
    std::vector<std::string> tokens;
    std::copy(std::istream_iterator<std::string>(stream),
              std::istream_iterator<std::string>(),
              std::back_inserter<std::vector<std::string>>(tokens));
    return tokens;
}

std::string nextOption(std::vector<std::string>& strings) {
    auto str = strings.back();
    strings.pop_back();
    return str;
}

void CClientMenu::Run(CRootMenu &rootMenu) {
    std::cout << "CClientMenu::Run" << std::endl;
    PrintCentre("Connecting to server...");
    CTcpClient tcpClient("127.0.0.1", 12346);
    tcpClient.BlockingConnect();

    PrintCentre("Waiting for server...");
    std::thread meleeThread;
    CMeleeClientStarter meleeStarter{rootMenu, *this};
    auto meleeRunning = true;
    while(meleeRunning) {
        tcpClient.ReadForever([&](const CTcpClient::MsgBuf& buf, size_t len) {
            auto tokens = msgBufToVec(buf, len);
            std::reverse(std::begin(tokens), std::end(tokens));
            const auto command = nextOption(tokens);

            if(command == "Start") {
                std::cout << "Starting the melee" << std::endl;
                //tokens gets modified, so no ref capture
                meleeThread = std::thread([&, tokens] {
                    meleeStarter.Start(tokens, mVersusMenu.GetClientOptions());
                });
            } else if(command == "Stop")  {
                std::cout << "Stopping the melee" << std::endl;
                meleeStarter.Stop();
                meleeRunning = false;
                meleeThread.join();
                return; //exits the lambda
            }
        });
    }

    tcpClient.Stop();
}


void CClientMenu::PrintCentre(const std::string& str) const {
    CCanvas screenCanvas(screen);
    screenCanvas.Clear();
    mFont.PrintCentre(screenCanvas, screenCanvas.GetWidth()/2,
                      screenCanvas.GetHeight()/2, makecol(255, 255, 255), -1,
                      str);
}
