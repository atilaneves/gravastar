#include "CClientMenu.hpp"
#include "MeleeStarter.hpp"
#include "CGravOptions.hpp"
#include "CGravUpdateServer.hpp"
#include "CCanvas.hpp"
#include "CFont.hpp"
#include "CGravMenu.hpp"
#include "CVersusMenu.hpp"
#include "CMeleeClient.hpp"
#include "CTcpClient.hpp"
#include "fontsdat.h"
#include <thread>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using boost::asio::ip::address_v4;


CClientMenu::CClientMenu(const CSprite *cursorSprite, CGravMenu& gravMenu):
    CCursorMenu<CStringMenu>(cursorSprite, "Client"),
    mVersusMenu(gravMenu.GetVersusMenu()),
    mFont(MetroStyleExtendedBoldItalic28) {

}

void CClientMenu::Run(CRootMenu &rootMenu) {
    CGravUpdateServer updateServer;
    std::thread updateThread{[&](){ updateServer.Run(); }};

    PrintCentre("Waiting for server...");
    CTcpClient tcpClient("127.0.0.1", 12346);
    tcpClient.BlockingConnect();

    std::thread readThread{[&] {
        tcpClient.ReadForever([](const CTcpClient::MsgBuf& buf, size_t len) {
            std::cout << "readThread lambda, len is "  << len << std::endl;
            std::cout.write(reinterpret_cast<const char*>(buf.data()), len);
            std::cout << std::endl;
        });
    }};

    rootMenu.StopSong();
    CSound sound("meleeStart");
    sound.PlayCentre();

    PrintCentre("Loading...");
    auto* melee = new CMeleeClient(GetGravOptions(), updateServer);
    assert(melee);
    melee->Run();
    delete melee;
    rootMenu.PlaySong();

    updateServer.Stop();
    updateThread.join();
}

void CClientMenu::PrintCentre(const std::string& str) {
    CCanvas screenCanvas(screen);
    screenCanvas.Clear();
    mFont.PrintCentre(screenCanvas, screenCanvas.GetWidth()/2,
                      screenCanvas.GetHeight()/2, makecol(255, 255, 255), -1,
                      str);
}

CGravOptions CClientMenu::GetGravOptions() const {
    const auto meleeType = "Survival"; //TODO: MeleeClient
    const auto levelNb = 1;
    const auto powerupRate = 0.0f;
    const CMeleeOptions meleeOptions{meleeType, levelNb, powerupRate};
    //const CClientOptions clientOptions = mVersusMenu.GetClientOptions();
    const CPilotInputOptions pilotInputOpts{"", 0, 0, 0, 0, 0, 0, 0, 0};
    const std::vector<std::string> ships{5, "Delta"};
    const CPilotOptions pilotOpts1{"P1", "Human", CTeam::sBlue, ships, pilotInputOpts};
    const CPilotOptions pilotOpts2{"P2", "Human", CTeam::sRed,  ships, pilotInputOpts};
    const CClientOptions clientOptions{{pilotOpts1, pilotOpts2},
                                       mVersusMenu.GetClientOptions()};
    return {meleeOptions, clientOptions};
}
