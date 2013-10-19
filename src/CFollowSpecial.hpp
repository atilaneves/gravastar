#ifndef CFOLLOWSPECIAL_H
#define CFOLLOWSPECIAL_H


#include "CSpecial.hpp"
class CSpriteVector;
class CFollowBluePrint;
class CFollower;


class CFollowSpecial: public CSpecial {

public:

    static const uint8_t CLASS_HASH = 10;

    CFollowSpecial(const CShipBluePrint &shipBluePrint,
                   CShip &ship, CLevel &level);

    virtual const CGravSprite& GetSprite() const override;
    virtual bool IsActive() const override;
    virtual CMoverObj* UseAt(const CVector2& pos, const CVector2& vel,
                             const std::string& name, bool shadow) override;
    virtual uint8_t GetSpecialHash() const override { return CLASS_HASH; }

private:

    const CFollowBluePrint& mBluePrint;
    const CSpriteVector&    mSprites;
    CFollower              *mFollower;

    virtual float GetDepletionScale(float dt) const override;
    virtual void  NotUsing() override;
};


#endif
