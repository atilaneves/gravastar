#include "MeleeStarter.hpp"
#include "CRootMenu.hpp"
#include "CGravOptions.hpp"
#include "CSound.hpp"
#include "CCanvas.hpp"
#include "CMeleeFactory.hpp"
#include "output.hpp"
#include <memory>

void startMeleeFromMenu(CRootMenu &rootMenu,
                        const CGravOptions& gravOptions) {
    rootMenu.StopSong();
    CSound{"meleeStart"}.PlayCentre();

    printCentre("Loading...");

    const auto meleeType = gravOptions.GetMeleeOptions().GetType();
    {
        const auto& factory = CMeleeFactory::Instance();
        std::unique_ptr<CMelee> melee{factory.CreateObject(meleeType, gravOptions)};
        assert(melee);
        melee->Run();
    }

    rootMenu.PlaySong();
}
