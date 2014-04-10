#ifndef CTHUNDERBLADE_H
#define CTHUNDERBLADE_H


#include "CShip.hpp"
class CWeaponFollow;


class CThunderblade: public CShip {

public:

  CThunderblade(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level);

  virtual bool CanMoveSuper() const override { return true; }
  virtual void UseSpecial(float dt) override;
  virtual void UseSuper(float dt, bool use = true) override;
  virtual void UseWeapon(float dt) override;

private:

  CWeaponFollow *mTempest;

  void SpawnBullet(float dt, float dAngle, float shotVel);

};


#endif
