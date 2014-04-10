#ifndef CHOMINGMISSILE_H
#define CHOMINGMISSILE_H


#include "CProjectile.hpp"


class CHomingMissile: public CProjectile {

public:

  CHomingMissile(const CProjBluePrint &bluePrint, CShip& ship,
                 const CVector2& pos, const CVector2& vel,
                 bool shadow = false);
  virtual ~CHomingMissile() { }

  virtual void Move(float dt) override;

private:

  int GetTargetIndex();

};


#endif
