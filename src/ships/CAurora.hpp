#ifndef CAURORA_H
#define CAURORA_H


#include "CShip.hpp"


class CAurora: public CShip {

public:

  CAurora(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level);

  virtual void LoseHull(float amount, CPilot &pilot) override;
  virtual void UseSpecial(float dt) override;
  virtual void UseSuper(float dt, bool use = true) override;
  virtual void UseWeapon(float dt) override;

private:

  void SpawnShard(float dt, float dAngle, bool shadow = false);

};


#endif
