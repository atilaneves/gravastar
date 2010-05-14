#ifndef CARROW_H
#define CARROW_H


#include "CShip.hpp"


class CArrow: public CShip {

public:

  CArrow(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level);

  virtual void UseSpecial(float dt);
  virtual void UseSuper(float dt, bool use = true);
  virtual void UseWeapon(float dt);


private:

  void SpawnShot(float dt, float dAngle);
  void SpawnMissile(float dt, float velAngle, bool shadow = false);

};


#endif
