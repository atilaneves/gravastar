#ifndef CWEAPONSTATS_H_
#define CWEAPONSTATS_H_

#include "CSpecialStatDrawer.hpp"
#include "CSuperStatsDrawer.hpp"

class CCanvas;


class CWeaponStats {
public:

    CWeaponStats(CSpecialStatDrawer specialDrawer, CSuperStatsDrawer superDrawer);
    void Draw(CCanvas& canvas) const;

private:

    CSpecialStatDrawer mSpecialDrawer;
    CSuperStatsDrawer mSuperDrawer;
};


#endif // CWEAPONSTATS_H_
