#ifndef CPROJECTILE_H
#define CPROJECTILE_H


class CProjBluePrint;
class CShip;
#include "CExplosive.hpp"
#include "CTimeCounter.hpp"
#include "CSpriteVector.hpp"

class CProjectile: public CExplosive {

public:

    CProjectile(const CProjBluePrint &bluePrint, CShip& ship,
                const CVector2& pos, const CVector2& vel, bool shadow = false);
    virtual ~CProjectile();

    virtual CVector2    CalcAcc() { return CVector2(0, 0); }
    virtual CSpriteObj* GetHitObj()  const { return mHitObj; }
            float       GetMaxDamage() const { return mMaxDamage; }
    virtual int         GetSpriteIndex() const { return mNose; }
    virtual void        Hit(CSpriteObj& obj, CScreenPos pos, float dt);
    virtual void        Hit(CShip& ship, CScreenPos pos, float dt);
    virtual void        Hit(CProjectile& projectile, CScreenPos pos, float dt);
    virtual void        HitTerrain(const CScreenPos &where, float dt);
    virtual void        LoseHull(float amount);
    virtual void        OutOfBounds(float angle) { (void)angle; Die();  }
    virtual void        SetVel(const CVector2& vel);
    virtual void        Update(float dt);


protected:

    float mMaxDamage, mDamage;
    int   mNose;


private:

    CTimeCounter  mShadowCounter;
    const CSpriteVector& mShadowSprites;
    CSpriteObj*   mHitObj;

    void CreateShadow();

    virtual void HitShipEffect(CShip& ship, CScreenPos pos, float dt);
    virtual bool WeShootOurOwn() { return false; }

};


#endif
