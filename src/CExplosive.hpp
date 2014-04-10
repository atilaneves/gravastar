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
  virtual void        Die()              { LoseHull(mHull); }
          float       GetMass()    const { return mMass; }
          float       GetMaxHull() const { return mMaxHull; }
  virtual CSpriteObj* GetHitObj()  const { return 0; }
          float       GetHull()    const { return mHull; }
  virtual bool        IsActive()         { return mHull > 0; }
  virtual bool        IsAlive()          { return mHull > 0; }
  virtual void        LoseHull(float amount);
  virtual void        Update(float dt);


protected:

  float mMass, mHull, mMaxHull, mShockWaveForce;
  CPilot& mPilot;
  const CSpriteVector& mExpSprites;
  CSound               mExpSound;

  virtual void HitTerrain(const CScreenPos &where, float dt) = 0;


};


#endif
