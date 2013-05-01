#include "CMeleeStart.hpp"
#include "MeleeStarter.hpp"
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
    startMeleeFromMenu(rootMenu, mVersusMenu.GetGravOptions());
}
