#ifndef PULSE_H
#define PULSE_H


#include "CProjectile.hpp"
#include "CSuperBeam.hpp"
#include "CTimeCounter.hpp"
#include <vector>


class CPulseLaser: public CProjectile {

public:

    CPulseLaser(const CProjBluePrint &bluePrint, CShip& ship,
                const CVector2& pos, const CVector2& vel, bool shadow = false);
    virtual ~CPulseLaser() {}

    virtual void AtDeath() override;
    virtual CLevelSprite Draw() override;
    virtual void Erase() override;
    virtual void Hit(CSpriteObj& obj, CScreenPos pos, float dt) override { }
    virtual void Hit(CShip& ship, CScreenPos pos, float dt) override;
    virtual void HitTerrain(const CScreenPos &where, float dt) override{ }
    virtual void Move(float dt) override;


private:

    CSuperBeam*  mBeam;
    CTimeCounter mCounter;

    virtual void HitShipEffect(CShip& ship, CScreenPos pos, float dt);

};

#endif
