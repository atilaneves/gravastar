#ifndef CDISCUS_H
#define CDISCUS_H


#include "CShip.hpp"


class CDiscus: public CShip {

public:

  CDiscus(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level);

  virtual CVector2 CalcAcc();
  virtual void 	   LoseHull(float amount, CPilot &pilot);
  virtual void 	   UseSpecial(float dt);
  virtual void 	   UseSuper(float dt, bool use = true);
  virtual void 	   UseWeapon(float dt);


private:

  void SpawnBullet(float dt, float dAngle, float shotVel);

};


#endif
