#ifndef CLEVELSPRITE_H
#define CLEVELSPRITE_H

#include <stdint.h>
#include <cstddef>

class Cereal;

class CLevelSprite {
public:
    CLevelSprite(uint16_t hash, uint16_t x, uint16_t y):
        mWasDrawn(true), mHash(hash), mX(x), mY(y) { }
    CLevelSprite():mWasDrawn(false), mHash(), mX(), mY() { }
    CLevelSprite(const CLevelSprite&) = default;
    bool WasDrawn() const { return mWasDrawn; }
    std::size_t GetHash() const { return mHash; }
    int GetX() const { return mX; }
    int GetY() const { return mY; }
    void cerealise(Cereal& cereal);

private:
    bool mWasDrawn;
    uint16_t mHash;
    uint16_t mX;
    uint16_t mY;
};



#endif // CLEVELSPRITE_H
