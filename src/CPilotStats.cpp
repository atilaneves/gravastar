#include "CPilotStats.hpp"
#include "CShip.hpp"
#include "CWeapons.hpp"
#include "CSuper.hpp"
#include "Cereal.hpp"


CPilotStats::CPilotStats(CWeaponStats weapon, CLivesStats lives, CHullStats hull):
    mWeapon(weapon),
    mLives(lives),
    mHull(hull) {

}


void CPilotStats::Draw(CCanvas& canvas) const {
    canvas.Clear(canvas.GetMask()); //we don't want garbage
    mLives.Draw(canvas);
    mHull.Draw(canvas);
    mWeapon.Draw(canvas);
}

void CPilotStats::cerealise(Cereal& cereal) {
    cereal.grain(mWeapon);
    cereal.grain(mLives);
    cereal.grain(mHull);
}
