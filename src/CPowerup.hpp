#ifndef CPOWERUP_H
#define CPOWERUP_H


#include "CSpriteObj.hpp"
#include <string>
class CGravSprite;
class CPowerups;


class CPowerup:public CSpriteObj {

public:

  CPowerup(CPowerups &powerups, CLevel &level,
           const CVector2 &pos, const CGravSprite& sprite);
  virtual ~CPowerup();


private:

  CPowerups&         mPowerups;
  const CGravSprite& mSprite;
  bool mActive;

  virtual void               AffectShip(CShip& ship) = 0;
  virtual void Hit(CSpriteObj &obj, CScreenPos pos, float dt) override;
  virtual void Hit(CShip &ship, CScreenPos pos, float dt) override;
  virtual bool IsActive() override { return mActive; }
  virtual const CGravSprite &GetSprite() const override { return mSprite; }
  virtual void Update(float dt) override;
};


#endif
