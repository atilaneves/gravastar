#ifndef CEXPLOSION_H
#define CEXPLOSION_H



#include "CSpriteObj.hpp"
#include "CSound.hpp"
#include "CSpriteVector.hpp"


class CExplosion: public CSpriteObj {

public:

 enum { kNbFrames=4, kSpeed = 120 };

  CExplosion(CLevel &level, const CVector2& pos, const CSpriteVector &sprites,
             const CSound &sound, float speed = kSpeed);

  virtual void Hit(CSpriteObj &obj, CScreenPos pos, float dt) override;
  virtual void Hit(CProjectile &proj, CScreenPos pos, float dt) override;
  virtual bool IsActive() override { return !mDead; }
  virtual const CGravSprite &GetSprite() const override {
    return *mSprites[int(mFrame)];
  }
  virtual void Update(float dt) override;

private:

  const CSpriteVector mSprites;
  CSound              mSound;
  float               mSpeed, mFrame;
  bool                mDead;

};

#endif
