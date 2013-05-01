#include "CClientMenu.hpp"
#include "MeleeStarter.hpp"
#include "CGravOptions.hpp"
#include "CGravUpdateServer.hpp"
#include "CCanvas.hpp"
#include "CFont.hpp"
#include "fontsdat.h"
#include <thread>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;


CClientMenu::CClientMenu(const CSprite *cursorSprite, CGravMenu& gravMenu):
    CCursorMenu<CStringMenu>(cursorSprite, "Client") {

}

static void connectToTcpServer() {
    boost::asio::io_service service;
    tcp::socket socket(service);

    const boost::asio::ip::address_v4 addr({{0x7f, 0, 0, 1}}); //local
    tcp::endpoint receiverEndpoint(addr, 12346);
    socket.connect(receiverEndpoint);

    for (;;) {
        std::array<char, 128> buf;
        boost::system::error_code error;

        const auto len = socket.read_some(boost::asio::buffer(buf), error);

        if(error == boost::asio::error::eof) {
            std::cout << "Connection closed by server" << std::endl;
            break; // Connection closed cleanly by peer.
        } else if(error) {
            std::cerr << "Error reading bytes from server" << std::endl;
            throw boost::system::system_error(error); // Some other error.
        }

        std::cout.write(buf.data(), len);
        std::cout << std::endl;
    }
}

void CClientMenu::Run(CRootMenu &rootMenu) {
    CGravUpdateServer udpServer;
    std::thread udpThread{[&](){ udpServer.Run(); }};

    connectToTcpServer();

    CCanvas screenCanvas(screen);
    screenCanvas.Clear();

    CFont font(MetroStyleExtendedBoldItalic28);
    font.PrintCentre(screenCanvas, screenCanvas.GetWidth()/2,
                     screenCanvas.GetHeight()/2, makecol(255, 255, 255), -1,
                     "Loading...");

    startMeleeFromMenu(rootMenu, CGravOptions{});

    udpServer.Stop();
    udpThread.join();
}
