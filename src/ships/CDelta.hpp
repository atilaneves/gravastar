#ifndef CDELTA_H
#define CDELTA_H


#include "CShip.hpp"


class CDelta: public CShip {

public:

  CDelta(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level);

  virtual void UseSpecial(float dt);
  virtual void UseSuper(float dt, bool use = true);
  virtual void UseWeapon(float dt);


private:

  void SpawnShot(float dt, float dAngle);
  void SpawnMissile(float dt, float velAngle, bool shadow = false);

};


#endif
