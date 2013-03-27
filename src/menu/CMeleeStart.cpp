#include "CMeleeStart.hpp"
#include "CMeleeFactory.hpp"
#include "CSound.hpp"
#include "CRootMenu.hpp"
#include "CGravMenu.hpp"
#include "CFont.hpp"
#include "fontsdat.h"


CMeleeStart::CMeleeStart(const CGravMenu &gravMenu,
                         const strings_t& levelNames):
    CCycleString("Level: ", levelNames, levelNames.size() - 1, 0),
    mGravMenu(gravMenu) {

}


void CMeleeStart::Run(CRootMenu &rootMenu) {
    rootMenu.StopSong();
    CSound sound("meleeStart");
    sound.PlayCentre();
  
    CCanvas screenCanvas(screen);
    screenCanvas.Clear();

    CFont font(MetroStyleExtendedBoldItalic28);
    font.PrintCentre(screenCanvas, screenCanvas.GetWidth()/2,
                     screenCanvas.GetHeight()/2, makecol(255, 255, 255), -1,
                     "Loading...");

    CGravOptions options = mGravMenu.GetGravOptions();
    std::string meleeType = options.GetMeleeOptions().GetType();
    CMelee* melee = CMeleeFactory::Instance().CreateObject(meleeType, options);
    assert(melee);
    melee->Run();
    delete melee;
    rootMenu.PlaySong();
}
