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

    CPilotStats(const CPilot &pilot, const CTeam& team,
                int score, float hull, float maxHull,
                const CShipStatSprite& sprite);

    void Draw(CBitmap& bitmap, int x, int y);

private:

    const CPilot& mPilot;
    CCanvas       mCanvas;
    CLivesStats   mLives;
    CHullStats    mHull;

};


#endif
