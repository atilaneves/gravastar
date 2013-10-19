#ifndef CFOLLOWSTATSDRAWER_H_
#define CFOLLOWSTATSDRAWER_H_

#include <stdint.h>
#include <cstddef>

class CTeam;
class CCanvas;


class CFollowStatsDrawer {
public:

    CFollowStatsDrawer(size_t spriteHash, uint8_t teamHash, float gauge, float maxGauge);
    void Draw(CCanvas& canvas) const;

private:

    size_t mSpriteHash;
    uint8_t mTeamHash;
    float mGauge;
    float mMaxGauge;
};


#endif // CFOLLOWSTATSDRAWER_H_
