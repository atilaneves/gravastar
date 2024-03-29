#ifndef CINDESTRUCTIBLE_H
#define CINDESTRUCTIBLE_H


#include "COneSpriteObj.hpp"
#include "CSound.hpp"


class CIndestructible: public COneSpriteObj {

public:

    CIndestructible(CLevel &level, const CVector2 &pos, CGravSprite *sprite,
                    const CSound& klang);

    virtual void Erase() override { Draw(); } // always there to be hit
    virtual void Hit(CSpriteObj &obj, CScreenPos pos, float dt) override;
    virtual void Hit(CShip &ship, CScreenPos pos, float dt) override;
    virtual void Hit(CProjectile &proj, CScreenPos pos, float dt) override;
    virtual void Update(float dt) override { (void)dt; }

private:

    CSound mKlang;

    virtual void ShipLanded(CShip& ship, float dt) { (void)ship;(void)dt;}


};


#endif
