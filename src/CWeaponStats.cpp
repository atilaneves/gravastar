#include "CWeaponStats.hpp"


CWeaponStats::CWeaponStats(CSpecialStatDrawer specialDrawer, CSuperStatsDrawer superDrawer):
    mSpecialDrawer(specialDrawer),
    mSuperDrawer(superDrawer) {
}

void CWeaponStats::Draw(CCanvas& canvas) const {
    mSpecialDrawer.Draw(canvas);
    mSuperDrawer.Draw(canvas);
}
