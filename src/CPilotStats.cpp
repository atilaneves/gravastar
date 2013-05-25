#include "CPilotStats.hpp"
#include "CPilot.hpp"
#include "CShip.hpp"
#include "CWeapons.hpp"
#include "CSuper.hpp"


CPilotStats::CPilotStats(const CPilot &pilot):
    mPilot(pilot), mCanvas(kCanvasWidth, kCanvasHeight),
    mLives(pilot, mCanvas), mHull(pilot, mCanvas) {

}


void CPilotStats::Draw(CBitmap &bitmap, int x, int y) {
    mCanvas.Clear(mCanvas.GetMask()); //we don't want garbage
    mLives.Draw();
    mHull.Draw();
    mPilot.GetShip().GetWeapons().DrawStats(mCanvas);
    mCanvas.Draw(bitmap, x, y); //draw it!
}
