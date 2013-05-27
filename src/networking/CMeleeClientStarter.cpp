#include "CMeleeClientStarter.hpp"
#include "CRootMenu.hpp"
#include "CMeleeClient.hpp"
#include "CSound.hpp"
#include "CClientMenu.hpp"
#include <thread>
#include <iostream>
using namespace std;

CMeleeClientStarter::CMeleeClientStarter(CRootMenu& rootMenu,
                                         const CClientMenu& clientMenu):
    mRootMenu(rootMenu), mClientMenu(clientMenu) {

}


void CMeleeClientStarter::Start(std::deque<std::string> options,
                                const CClientOptions& vsClientOptions) {
    mRootMenu.StopSong();
    CSound sound("meleeStart");
    sound.PlayCentre();

    const unsigned pilotIndex = std::stoi(nextOption(options));
    cout << "pilotIndex is " << pilotIndex;
    CGravUpdateServer updateServer{pilotIndex};
    std::thread updateThread{[&](){ updateServer.Run(); }};

    mClientMenu.PrintCentre("Loading...");
    mMelee.reset(new CMeleeClient{GetGravOptions(options, vsClientOptions),
                                  updateServer});
    mMelee->Run();

    updateServer.Stop();
    updateThread.join();

    mRootMenu.PlaySong();
}

void CMeleeClientStarter::Stop() {
    mMelee->Stop();
}

CGravOptions CMeleeClientStarter::GetGravOptions(std::deque<std::string>& options,
                                                 const CClientOptions& vsClientOptions) const {
    const auto levelNb    = std::stoi(nextOption(options));
    const auto nbPilots   = std::stoi(nextOption(options));
    const auto nbShips    = std::stoi(nextOption(options));
    cout << "level " << levelNb << " pilots: " << nbPilots << " ships: " << nbShips << endl;

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

    const CClientOptions clientOptions{allPilotOpts, vsClientOptions};
    return {meleeOptions, clientOptions};
}
