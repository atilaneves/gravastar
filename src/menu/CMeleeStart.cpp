#include "CMeleeStart.hpp"
#include "CMeleeFactory.hpp"
#include "CSound.hpp"
#include "CRootMenu.hpp"
#include "CVersusMenu.hpp"
#include "CFont.hpp"
#include "fontsdat.h"


CMeleeStart::CMeleeStart(const CVersusMenu &versusMenu,
                         const strings_t& levelNames):
    CCycleString("Level: ", levelNames, levelNames.size() - 1, 0),
    mVersusMenu(versusMenu) {

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

    const CGravOptions options = mVersusMenu.GetGravOptions();
    const std::string meleeType = options.GetMeleeOptions().GetType();
    CMelee* melee = CMeleeFactory::Instance().CreateObject(meleeType, options);
    assert(melee);
    melee->Run();
    delete melee;
    rootMenu.PlaySong();
}
