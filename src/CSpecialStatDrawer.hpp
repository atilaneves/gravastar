#ifndef CSPECIALSTATDRAWER_H_
#define CSPECIALSTATDRAWER_H_

#include <cstddef>
#include <stdint.h>
class CCanvas;


class CSpecialStatDrawer {
public:

    CSpecialStatDrawer(uint8_t specialHash, size_t spriteHash, uint8_t teamHash,
                       float gauge, float maxGauge);

    void Draw(CCanvas& canvas) const;

private:

    uint8_t mSpecialHash;
    size_t mSpriteHash;
    uint8_t mTeamHash;
    float mGauge;
    float mMaxGauge;
};


#endif // CSPECIALSTATDRAWER_H_
