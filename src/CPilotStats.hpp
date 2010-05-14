#ifndef CPILOTSTATS_H
#define CPILOTSTATS_H


class CPilot;
class CShipStatSprite;
#include "CCanvas.hpp"
#include "CHullStats.hpp"
#include "CLivesStats.hpp"


class CPilotStats {

public:

  enum { kCanvasWidth = 100, kCanvasHeight = 50 };

  CPilotStats(const CPilot &pilot);

  void Draw(CBitmap& bitmap, int x, int y);
  void SetStatSprite(const CShipStatSprite *sprite) {
    mLives.SetStatSprite(sprite); }


private:

  const CPilot& mPilot;
  CCanvas       mCanvas;
  CLivesStats   mLives;
  CHullStats    mHull;

};


#endif
