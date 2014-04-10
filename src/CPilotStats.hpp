#ifndef CPILOTSTATS_H
#define CPILOTSTATS_H


class CShip;
class CShipStatSprite;
class Cereal;
#include "CCanvas.hpp"
#include "CHullStats.hpp"
#include "CLivesStats.hpp"
#include "CWeaponStats.hpp"


class CPilotStats {

public:

    CPilotStats() {}
    CPilotStats(CWeaponStats weapon, CLivesStats lives, CHullStats hull);

    void Draw(CCanvas& canvas) const;
    void cerealise(Cereal& cereal);

private:

    CWeaponStats mWeapon;
    CLivesStats   mLives;
    CHullStats    mHull;

};


#endif
