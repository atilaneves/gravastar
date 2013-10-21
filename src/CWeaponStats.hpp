#ifndef CWEAPONSTATS_H_
#define CWEAPONSTATS_H_

#include "CSpecialStatDrawer.hpp"
#include "CSuperStatsDrawer.hpp"

class CCanvas;


class CWeaponStats {
public:

    CWeaponStats() { }
    CWeaponStats(CSpecialStatDrawer specialDrawer, CSuperStatsDrawer superDrawer);
    void Draw(CCanvas& canvas) const;
    void cerealise(Cereal& cereal);

private:

    CSpecialStatDrawer mSpecialDrawer;
    CSuperStatsDrawer mSuperDrawer;
};


#endif // CWEAPONSTATS_H_
