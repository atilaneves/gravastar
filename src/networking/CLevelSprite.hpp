#ifndef CLEVELSPRITE_H
#define CLEVELSPRITE_H


class CLevelSprite {
public:
    CLevelSprite(size_t hash, int x, int y):mWasDrawn(true), mHash(hash), mX(x), mY(y) { }
    CLevelSprite():mWasDrawn(false), mHash(), mX(), mY() { }
    bool WasDrawn() const { return mWasDrawn; }
    size_t GetHash() const { return mHash; }
    int GetX() const { return mX; }
    int GetY() const { return mY; }
private:
    const bool mWasDrawn;
    const size_t mHash;
    const int mX;
    const int mY;
};



#endif // CLEVELSPRITE_H
