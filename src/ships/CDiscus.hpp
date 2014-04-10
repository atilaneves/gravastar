#ifndef CDISCUS_H
#define CDISCUS_H


#include "CShip.hpp"


class CDiscus: public CShip {

public:

  CDiscus(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level);

  virtual CVector2 CalcAcc() override;
  virtual void LoseHull(float amount, CPilot &pilot) override;
  virtual void UseSpecial(float dt) override;
  virtual void UseSuper(float dt, bool use = true) override;
  virtual void UseWeapon(float dt) override;

private:

  void SpawnBullet(float dt, float dAngle, float shotVel);

};


#endif
