#include "CPilotStats.hpp"
#include "CShip.hpp"
#include "CWeapons.hpp"
#include "CSuper.hpp"



CPilotStats::CPilotStats(CSpecialStatDrawer specialDrawer, CSuperStatsDrawer superDrawer,
                         const CTeam& team,
                         int score, float hull, float maxHull,
                         const CShipStatSprite& sprite):
    mWeapon(specialDrawer, superDrawer),
    mLives(team, sprite, score),
    mHull(team, hull, maxHull) {

}


void CPilotStats::Draw(CCanvas& canvas) const {
    canvas.Clear(canvas.GetMask()); //we don't want garbage
    mLives.Draw(canvas);
    mHull.Draw(canvas);
    mWeapon.Draw(canvas);
}
