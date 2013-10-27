#include "CMeleeStart.hpp"
#include "MeleeStarter.hpp"
#include "CVersusMenu.hpp"


CMeleeStart::CMeleeStart(const CVersusMenu &versusMenu,
                         const strings_t& levelNames):
    CCycleString("Level: ", levelNames, levelNames.size() - 1, 0),
    mVersusMenu(versusMenu) {

}


void CMeleeStart::Run(CRootMenu &rootMenu) {
    startMeleeFromMenu(rootMenu, mVersusMenu.GetGravOptions());
}
