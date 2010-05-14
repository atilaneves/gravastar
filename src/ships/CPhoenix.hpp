#ifndef CPHOENIX_H
#define CPHOENIX_H


#include "CShip.hpp"


class CPhoenix: public CShip {

public:

  CPhoenix(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level);

  virtual void UseSpecial(float dt);
  virtual void UseSuper(float dt, bool use = true);
  virtual void UseWeapon(float dt);


private:

  void SpawnShot(float dt, float dAngle);
  void SpawnMissile(float dt, float velAngle, bool shadow = false);

};


#endif
