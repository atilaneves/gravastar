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
#include <algorithm>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using boost::asio::ip::address_v4;


CClientMenu::CClientMenu(const CSprite *cursorSprite, CGravMenu& gravMenu):
    CCursorMenu<CStringMenu>(cursorSprite, "Client"),
    mVersusMenu(gravMenu.GetVersusMenu()),
    mFont(MetroStyleExtendedBoldItalic28) {

}

static std::vector<std::string> msgBufToVec(const CTcpClient::MsgBuf& buf, size_t len) {
    std::string bufStr{buf.cbegin(), buf.cbegin() + len};
    std::istringstream stream{bufStr};
    std::vector<std::string> tokens;
    std::copy(std::istream_iterator<std::string>(stream),
              std::istream_iterator<std::string>(),
              std::back_inserter<std::vector<std::string>>(tokens));
    return tokens;
}

static std::string nextOption(std::vector<std::string>& strings) {
    auto str = strings.back();
    strings.pop_back();
    return str;
}

void CClientMenu::Run(CRootMenu &rootMenu) {
    PrintCentre("Connecing to server...");
    CTcpClient tcpClient("127.0.0.1", 12346);
    tcpClient.BlockingConnect();

    PrintCentre("Waiting for server...");
    for(;;) {
        tcpClient.ReadForever([&](const CTcpClient::MsgBuf& buf, size_t len) {
            auto tokens = msgBufToVec(buf, len);
            std::reverse(std::begin(tokens), std::end(tokens));
            const auto command = nextOption(tokens);
            if(command == "Start") StartMeleeClient(rootMenu, tokens);
        });
    }

    tcpClient.Stop();
}


void CClientMenu::StartMeleeClient(CRootMenu &rootMenu, std::vector<std::string>& options) const {
    rootMenu.StopSong();
    CSound sound("meleeStart");
    sound.PlayCentre();

    CGravUpdateServer updateServer;
    std::thread updateThread{[&](){ updateServer.Run(); }};

    PrintCentre("Loading...");
    auto* melee = new CMeleeClient(GetGravOptions(options), updateServer);
    assert(melee);
    melee->Run();
    delete melee;
    rootMenu.PlaySong();

    updateServer.Stop();
    updateThread.join();
}


void CClientMenu::PrintCentre(const std::string& str) const {
    CCanvas screenCanvas(screen);
    screenCanvas.Clear();
    mFont.PrintCentre(screenCanvas, screenCanvas.GetWidth()/2,
                      screenCanvas.GetHeight()/2, makecol(255, 255, 255), -1,
                      str);
}

CGravOptions CClientMenu::GetGravOptions(std::vector<std::string>& options) const {
    const auto levelNb  = std::stoi(nextOption(options));
    const auto nbPilots = std::stoi(nextOption(options));
    const auto nbShips  = std::stoi(nextOption(options));

    std::vector<CPilotOptions> allPilotOpts;
    for(int i = 0; i < nbPilots; ++i) {
        const auto name = nextOption(options);
        const auto type = nextOption(options);
        const auto& team = CTeam::FindByName(nextOption(options));
        std::vector<std::string> ships;
        for(int j = 0; j < nbShips; ++j) {
            ships.push_back(nextOption(options));
        }

        const CPilotInputOptions pilotInputOpts{"", 0, 0, 0, 0, 0, 0, 0, 0};
        allPilotOpts.emplace_back(name, type, team, ships, pilotInputOpts);
    }

    const auto meleeType = "Client";
    const auto powerupRate = 0.0f;
    const CMeleeOptions meleeOptions{meleeType, levelNb, powerupRate};

    const CClientOptions clientOptions{allPilotOpts,
                                       mVersusMenu.GetClientOptions()};
    return {meleeOptions, clientOptions};
}
