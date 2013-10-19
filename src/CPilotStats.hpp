#ifndef CPILOTSTATS_H
#define CPILOTSTATS_H


class CShip;
class CShipStatSprite;
#include "CCanvas.hpp"
#include "CHullStats.hpp"
#include "CLivesStats.hpp"
#include "CWeaponStats.hpp"


class CPilotStats {

public:

    CPilotStats(CSpecialStatDrawer specialDrawer, CSuperStatsDrawer superDrawer,
                const CTeam& team,
                int score, float hull, float maxHull,
                const CShipStatSprite& sprite);

    void Draw(CCanvas& canvas) const;

private:

    CWeaponStats mWeapon;
    CLivesStats   mLives;
    CHullStats    mHull;

};


#endif
