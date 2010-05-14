#ifndef CNIMBUS_H
#define CNIMBUS_H


#include "CShip.hpp"


class CNimbus: public CShip {

public:

  CNimbus(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level);

  virtual void UseSpecial(float dt);
  virtual void UseSuper(float dt, bool use = true);
  virtual void UseWeapon(float dt);


private:

  void SpawnShot(float dt, float dAngle);

};


#endif
