#include "CClientMenu.hpp"
#include "MeleeStarter.hpp"
#include "CGravOptions.hpp"
#include "CGravUpdateServer.hpp"
#include "CCanvas.hpp"
#include "CFont.hpp"
#include "CGravMenu.hpp"
#include "CVersusMenu.hpp"
#include "CMeleeClient.hpp"
#include "fontsdat.h"
#include <thread>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using boost::asio::ip::address_v4;


CClientMenu::CClientMenu(const CSprite *cursorSprite, CGravMenu& gravMenu):
    CCursorMenu<CStringMenu>(cursorSprite, "Client"),
    mVersusMenu(gravMenu.GetVersusMenu()) {

}

std::vector<char> gRecvBuffer;
static bool connectToTcpServer() {
    boost::asio::io_service service;
    tcp::socket socket(service);

    const address_v4 addr = address_v4::from_string("127.0.0.1");
    tcp::endpoint receiverEndpoint(addr, 12346);
    socket.connect(receiverEndpoint);

    for (;;) {
        std::array<char, 1024> buf;
        boost::system::error_code error;

        const auto len = socket.read_some(boost::asio::buffer(buf), error);

        if(error == boost::asio::error::eof) {
            std::cout << "Connection closed by server. Received:" << std::endl;
            break; // Connection closed cleanly by peer.
        } else if(error) {
            std::cerr << "Error reading bytes from server" << std::endl;
            //throw boost::system::system_error(error); // Some other error.
            return false;
        }

        gRecvBuffer.clear();
        gRecvBuffer.insert(std::begin(gRecvBuffer), std::begin(buf), std::end(buf));
        std::cout.write(buf.data(), len);
        std::cout << std::endl;       
        return true;
    }
    return true;
}

void CClientMenu::Run(CRootMenu &rootMenu) {
    CGravUpdateServer udpServer;
    std::thread udpThread{[&](){ udpServer.Run(); }};

    CCanvas screenCanvas(screen);
    screenCanvas.Clear();

    CFont font(MetroStyleExtendedBoldItalic28);
    font.PrintCentre(screenCanvas, screenCanvas.GetWidth()/2,
                     screenCanvas.GetHeight()/2, makecol(255, 255, 255), -1,
                     "Waiting for server...");

    std::unique_ptr<std::thread> tcpThread;
    for(;;) {
        try {
            //tcpThread.reset(new std::thread([]{connectToTcpServer();}));
            while(!connectToTcpServer()) ;
            break;
        } catch(...) {
            continue;
        }
    }

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
    const CGravOptions gravOptions{meleeOptions, clientOptions};

    rootMenu.StopSong();
    CSound sound("meleeStart");
    sound.PlayCentre();
  
    //CCanvas screenCanvas(screen);
    screenCanvas.Clear();

    //CFont font(MetroStyleExtendedBoldItalic28);
    font.PrintCentre(screenCanvas, screenCanvas.GetWidth()/2,
                     screenCanvas.GetHeight()/2, makecol(255, 255, 255), -1,
                     "Loading...");

    auto* melee = new CMeleeClient(gravOptions, udpServer);
    assert(melee);
    melee->Run();
    delete melee;
    rootMenu.PlaySong();

    udpServer.Stop();
    udpThread.join();
}
