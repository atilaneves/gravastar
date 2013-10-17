#ifndef CPILOTSTATS_H
#define CPILOTSTATS_H


class CPilot;
class CShipStatSprite;
#include "CCanvas.hpp"
#include "CHullStats.hpp"
#include "CLivesStats.hpp"


class CPilotStats {

public:

    CPilotStats(const CPilot &pilot, const CTeam& team,
                int score, float hull, float maxHull,
                const CShipStatSprite& sprite);

    void Draw(CCanvas& canvas) const;

private:

    const CPilot& mPilot;
    CLivesStats   mLives;
    CHullStats    mHull;

};


#endif
