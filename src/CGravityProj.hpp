#ifndef CGRAVITYPROJ_H
#define CGRAVITYPROJ_H


#include "CProjectile.hpp"


class CGravityProj: public CProjectile {

public:

  CGravityProj(const CProjBluePrint &bluePrint, CShip& ship,
               const CVector2& pos, const CVector2& vel, bool shadow = false);

  virtual CVector2 CalcAcc() override;

private:
  virtual bool WeShootOurOwn() override { return true; } // we do
};

#endif
