#include "MeleeStarter.hpp"
#include "CRootMenu.hpp"
#include "CGravOptions.hpp"
#include "CSound.hpp"
#include "CCanvas.hpp"
#include "CFont.hpp"
#include "CMeleeFactory.hpp"
#include "fontsdat.h"
#include <memory>

void startMeleeFromMenu(CRootMenu &rootMenu,
                        const CGravOptions& gravOptions) {
    rootMenu.StopSong();
    CSound sound("meleeStart");
    sound.PlayCentre();

    CCanvas screenCanvas(screen);
    screenCanvas.Clear();

    CFont font(MetroStyleExtendedBoldItalic28);
    font.PrintCentre(screenCanvas, screenCanvas.GetWidth()/2,
                     screenCanvas.GetHeight()/2, makecol(255, 255, 255), -1,
                     "Loading...");

    const auto meleeType = gravOptions.GetMeleeOptions().GetType();
    {
        const auto& factory = CMeleeFactory::Instance();
        std::unique_ptr<CMelee> melee{factory.CreateObject(meleeType, gravOptions)};
        assert(melee);
        melee->Run();
    }

    rootMenu.PlaySong();
}
