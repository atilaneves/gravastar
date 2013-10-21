#include "CWeaponStats.hpp"
#include "Cereal.hpp"


CWeaponStats::CWeaponStats(CSpecialStatDrawer specialDrawer, CSuperStatsDrawer superDrawer):
    mSpecialDrawer(specialDrawer),
    mSuperDrawer(superDrawer) {
}

void CWeaponStats::Draw(CCanvas& canvas) const {
    mSpecialDrawer.Draw(canvas);
    mSuperDrawer.Draw(canvas);
}

void CWeaponStats::cerealise(Cereal& cereal) {
    cereal.grain(mSpecialDrawer);
    cereal.grain(mSuperDrawer);
}
