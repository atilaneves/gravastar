#ifndef CSPECIALSTATDRAWER_H_
#define CSPECIALSTATDRAWER_H_

#include <cstddef>
#include <stdint.h>
class CCanvas;
class Cereal;

class CSpecialStatDrawer {
public:

    CSpecialStatDrawer() {}
    CSpecialStatDrawer(uint8_t specialHash, size_t spriteHash, uint8_t teamHash,
                       uint8_t gauge, uint8_t maxGauge);

    void Draw(CCanvas& canvas) const;
    void cerealise(Cereal& cereal);

private:

    uint8_t mSpecialHash;
    size_t mSpriteHash;
    uint8_t mTeamHash;
    uint8_t mGauge;
    uint8_t mMaxGauge;
};


#endif // CSPECIALSTATDRAWER_H_
