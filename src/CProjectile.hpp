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

    virtual CVector2 CalcAcc() override { return CVector2(0, 0); }
    virtual CSpriteObj *GetHitObj() const override { return mHitObj; }
            float       GetMaxDamage() const { return mMaxDamage; }
            virtual int GetSpriteIndex() const override { return mNose; }
            virtual void Hit(CSpriteObj &obj, CScreenPos pos,
                             float dt) override;
            virtual void Hit(CShip &ship, CScreenPos pos, float dt) override;
            virtual void Hit(CProjectile &projectile, CScreenPos pos,
                             float dt) override;
            virtual void HitTerrain(const CScreenPos &where, float dt) override;
            virtual void LoseHull(float amount) override;
            virtual void OutOfBounds(float angle) override {
              (void)angle;
              Die();
            }
    virtual void        SetVel(const CVector2& vel);
    virtual void Update(float dt) override;

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
