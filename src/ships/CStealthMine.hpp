#ifndef STEALTHMINE_H
#define STEALTHMINE_H


#include "CProjectile.hpp"
#include "CTimeCounter.hpp"
class CGravSprite;


class CStealthMine: public CProjectile {

public:

  CStealthMine(const CProjBluePrint &bluePrint, CShip& ship,
	       const CVector2& pos, const CVector2& vel, bool shadow = false);
  virtual ~CStealthMine();

  virtual CVector2 CalcAcc() override;
  virtual const CGravSprite &GetSprite() const override;
  virtual void Hit(CShip &ship, CScreenPos pos, float dt) override;
  virtual void Hit(CProjectile &proj, CScreenPos pos, float dt) override;
  virtual void Update(float dt) override;

private:

  bool mIsInvisible;
  CTimeCounter mCounter;

  static int sNbStealths;
  static CGravSprite* sInvisible;

  CGravSprite* CreateInvisible();

};

#endif
