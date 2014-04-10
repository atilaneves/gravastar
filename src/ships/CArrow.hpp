#ifndef CARROW_H
#define CARROW_H


#include "CShip.hpp"


class CArrow: public CShip {

public:

  CArrow(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level);

  virtual void UseSpecial(float dt) override;
  virtual void UseSuper(float dt, bool use = true) override;
  virtual void UseWeapon(float dt) override;

private:

  void SpawnShot(float dt, float dAngle);
  void SpawnMissile(float dt, float velAngle, bool shadow = false);

};


#endif
