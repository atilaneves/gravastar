#ifndef CEXPLOSIVE_H
#define CEXPLOSIVE_H


#include "CMoverObj.hpp"
#include "CSpriteVector.hpp"
#include "CSound.hpp"
class CExplosiveBluePrint;
class CPilot;


class CExplosive: public CMoverObj {

public:

  CExplosive(const CExplosiveBluePrint &bluePrint, CLevel &level,
             CPilot& pilot,
             const CVector2 &pos, const CVector2 &vel, float maxHull);

  virtual void        AtDeath();
  virtual void Die() override { LoseHull(mHull); }
          float       GetMass()    const { return mMass; }
          float       GetMaxHull() const { return mMaxHull; }
          virtual CSpriteObj *GetHitObj() const { return nullptr; }
          float       GetHull()    const { return mHull; }
          virtual bool IsActive() override { return mHull > 0; }
          virtual bool IsAlive() override { return mHull > 0; }
  virtual void        LoseHull(float amount);
  virtual void Update(float dt) override;

protected:

  float mMass, mHull, mMaxHull, mShockWaveForce;
  CPilot& mPilot;
  const CSpriteVector& mExpSprites;
  CSound               mExpSound;

  virtual void HitTerrain(const CScreenPos &where, float dt) override = 0;


};


#endif
