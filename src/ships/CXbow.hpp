#ifndef CXBOW_H
#define CXBOW_H


#include "CShip.hpp"
class CFlicker;


class CXbow: public CShip {

public:

  CXbow(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level);

          bool     CanSpecial() { return GetWeapons().GetSpecialGauge() > 0.2; }
  virtual void     Hit(CProjectile& proj, CScreenPos pos, float dt);
  virtual void 	   UseSpecial(float dt);
  virtual void 	   UseSuper(float dt, bool use = true);
  virtual void 	   UseWeapon(float dt);


private:

  CMoverObj *mDeflector;

  bool IsWithinCone(const CVector2& pos) const;

};


#endif
