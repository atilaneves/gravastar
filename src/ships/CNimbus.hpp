#ifndef CNIMBUS_H
#define CNIMBUS_H


#include "CShip.hpp"


class CNimbus: public CShip {

public:

  CNimbus(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level);

  virtual void UseSpecial(float dt) override;
  virtual void UseSuper(float dt, bool use = true) override;
  virtual void UseWeapon(float dt) override;

private:

  void SpawnShot(float dt, float dAngle);

};


#endif
