#ifndef CLUNA_H
#define CLUNA_H


#include "CShip.hpp"


class CLuna: public CShip {

public:

  CLuna(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level);

  virtual void UseSpecial(float dt) override;
  virtual void UseSuper(float dt, bool use = true) override;
  virtual void UseWeapon(float dt) override;

private:

  void SpawnShot(float dt, int shotIndex, float shotVel);

};


#endif
