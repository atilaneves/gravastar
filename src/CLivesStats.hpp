#ifndef CSTATSLIVES_H
#define CSTATSLIVES_H


#include <cstdint>
#include <cstddef>
class CCanvas;
class CTeam;
class CShipStatSprite;
class Cereal;


class CLivesStats {
public:

    CLivesStats() {}
    CLivesStats(uint8_t teamHash, size_t spriteHash, uint8_t score);
    void Draw(CCanvas& canvas) const;
    void cerealise(Cereal& cereal);

private:

    uint8_t mTeamHash;
    size_t mSpriteHash;
    uint8_t mScore;
};


#endif
