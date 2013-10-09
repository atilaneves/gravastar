#include "CMeleeClientStarter.hpp"
#include "CRootMenu.hpp"
#include "CMeleeClient.hpp"
#include "CSound.hpp"
#include "CGravUpdateServer.hpp"
#include "stl_utils.hpp"
#include "output.hpp"
#include <thread>
#include <iostream>


using namespace std;


CMeleeClientStarter::CMeleeClientStarter(CRootMenu& rootMenu,
                                         uint16_t serverUdpPort):
    mRootMenu(rootMenu),
    mServerUdpPort(serverUdpPort) {

}


void CMeleeClientStarter::Start(std::deque<std::string> options,
                                const CClientOptions& vsClientOptions) {
    mRootMenu.StopSong();
    CSound sound("meleeStart");
    sound.PlayCentre();

    const unsigned pilotIndex = std::stoi(popFront(options));
    CGravUpdateServer updateServer{mServerUdpPort, pilotIndex};
    std::thread updateThread{[&](){ updateServer.Run(); }};

    printCentre("Loading...");
    mMelee.reset(new CMeleeClient{GetGravOptions(options, vsClientOptions),
                                  updateServer});
    mMelee->Run();

    updateServer.Stop();
    updateThread.join();

    mRootMenu.PlaySong();
}

void CMeleeClientStarter::Stop(int winner) {
    mMelee->Stop(winner);
}

CGravOptions CMeleeClientStarter::GetGravOptions(std::deque<std::string>& options,
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
