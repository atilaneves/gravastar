#ifndef CPROJSPECIAL_H
#define CPROJSPECIAL_H


#include "CSpecial.hpp"
class CProjBluePrint;


class CProjSpecial: public CSpecial {
public:

    static const uint8_t CLASS_HASH = 42;

    CProjSpecial(const CShipBluePrint &shipBluePrint,
                 CShip &ship, CLevel &level);

    virtual const CGravSprite& GetSprite() const override;

    virtual bool IsActive() const override { return true; }
    virtual CMoverObj* UseAt(const CVector2& pos, const CVector2& vel,
                             const std::string& name, bool shadow) override;
    virtual uint8_t GetSpecialHash() const override { return CLASS_HASH; }

private:

    const CProjBluePrint&  mBluePrint;

    virtual float GetDepletionScale(float dt) const override { return 1; }
    virtual void  NotUsing() override { }

};


#endif
