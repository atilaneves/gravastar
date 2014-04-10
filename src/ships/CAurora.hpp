#ifndef CAURORA_H
#define CAURORA_H


#include "CShip.hpp"


class CAurora: public CShip {

public:

  CAurora(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level);

  virtual void LoseHull(float amount, CPilot &pilot);
  virtual void UseSpecial(float dt);
  virtual void UseSuper(float dt, bool use = true);
  virtual void UseWeapon(float dt);


private:

  void SpawnShard(float dt, float dAngle, bool shadow = false);

};


#endif
