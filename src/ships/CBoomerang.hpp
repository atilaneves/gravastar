#ifndef BOOMERANG_H
#define BOOMERANG_H


#include "CProjectile.hpp"


class CBoomerang: public CProjectile {

public:

  CBoomerang(const CProjBluePrint &bluePrint, CShip& ship,
	     const CVector2& pos, const CVector2& vel, bool shadow = false);
  virtual ~CBoomerang() {} 

  virtual void Move(float dt);


private:

  virtual void HitShipEffect(CShip& ship, CScreenPos pos, float dt);

};

#endif
