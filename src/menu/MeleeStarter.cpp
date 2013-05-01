#include "MeleeStarter.hpp"
#include "CRootMenu.hpp"
#include "CGravOptions.hpp"
#include "CSound.hpp"
#include "CCanvas.hpp"
#include "CFont.hpp"
#include "CMeleeFactory.hpp"
#include "fontsdat.h"

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

    const std::string meleeType = gravOptions.GetMeleeOptions().GetType();
    CMelee* melee = CMeleeFactory::Instance().CreateObject(meleeType, gravOptions);
    assert(melee);
    melee->Run();
    delete melee;
    rootMenu.PlaySong();

}
