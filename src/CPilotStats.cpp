#include "CPilotStats.hpp"
#include "CPilot.hpp"
#include "CShip.hpp"
#include "CWeapons.hpp"
#include "CSuper.hpp"



CPilotStats::CPilotStats(const CPilot &pilot, const CTeam& team,
                         int score, float hull, float maxHull,
                         const CShipStatSprite& sprite):
    mPilot(pilot),
    mLives(team, sprite, score),
    mHull(team, hull, maxHull) {

}


void CPilotStats::Draw(CCanvas& canvas) const {
    canvas.Clear(canvas.GetMask()); //we don't want garbage
    mLives.Draw(canvas);
    mHull.Draw(canvas);
    mPilot.GetShip().GetWeapons().DrawStats(canvas);
}
