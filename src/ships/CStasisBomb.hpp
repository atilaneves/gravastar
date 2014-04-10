#ifndef STASISBOMB_H
#define STASISBOMB_H


#include "CProjectile.hpp"


class CStasisBomb: public CProjectile {

public:

  CStasisBomb(const CProjBluePrint &bluePrint, CShip& ship,
	     const CVector2& pos, const CVector2& vel, bool shadow = false);
  virtual ~CStasisBomb() {} 


private:
  virtual void AtDeath() override;
};

#endif
