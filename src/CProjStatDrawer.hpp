#ifndef CPROJSTATDRAWER_H_
#define CPROJSTATDRAWER_H_

#include <stdint.h>
#include <cstddef>

class CCanvas;
class CTeam;

class CProjStatDrawer {
public:

    CProjStatDrawer(size_t spriteHash, uint8_t teamHash, float gauge, float maxGauge);
    void Draw(CCanvas& canvas) const;

private:

    size_t mSpriteHash;
    uint8_t mTeamHash;
    float mGauge;

};

#endif // CPROJSTATDRAWER_H_
