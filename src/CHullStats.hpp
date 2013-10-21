#ifndef CHULLSTATS_H
#define CHULLSTATS_H


#include <stdint.h>
class CCanvas;
class CTeam;
class Cereal;


class CHullStats {

public:

    CHullStats() {}
    CHullStats(uint8_t teamHash, int8_t hull, int8_t maxHull);

    void Draw(CCanvas &canvas) const;
    void cerealise(Cereal& cereal);

private:

    uint8_t mTeamHash;
    int8_t mHull;
    int8_t mMaxHull;
};


#endif
