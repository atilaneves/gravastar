#ifndef CSHIPCOLLIDER_H
#define CSHIPCOLLIDER_H


class CShip;
class CLevel;
#include "CSound.hpp"
#include "CScreenPos.hpp"
#include "CVector2.hpp"


class CShipCollider {

public:

  CShipCollider(CShip& ship, CLevel &level, const CSound &klang);

  bool     BouncedOff(const CScreenPos& pos, float& edgeAngle);
  void     Hit(CShip &ship, float dt);
  void     Klang();
  void     LandDamage(float dt) const;
  CVector2 VelAfterFriction(float angle, const CVector2& vel) const;

private:

  CShip&  mShip;
  CLevel& mLevel;
  CSound  mKlang;

};


#endif
