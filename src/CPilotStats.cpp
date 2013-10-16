#include "CPilotStats.hpp"
#include "CPilot.hpp"
#include "CShip.hpp"
#include "CWeapons.hpp"
#include "CSuper.hpp"



CPilotStats::CPilotStats(const CPilot &pilot, const CTeam& team,
                         int score, float hull, float maxHull,
                         const CShipStatSprite& sprite):
    mPilot(pilot), mCanvas(kCanvasWidth, kCanvasHeight),
    mLives(mCanvas, team, sprite, score),
    mHull(mCanvas, team, hull, maxHull) {

}


void CPilotStats::Draw(CBitmap &bitmap, int x, int y) {
    mCanvas.Clear(mCanvas.GetMask()); //we don't want garbage
    mLives.Draw();
    mHull.Draw();
    mPilot.GetShip().GetWeapons().DrawStats(mCanvas);
    mCanvas.Draw(bitmap, x, y); //draw it!
}
