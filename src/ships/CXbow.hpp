#ifndef CXBOW_H
#define CXBOW_H


#include "CShip.hpp"
class CFlicker;


class CXbow: public CShip {

public:

  CXbow(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level);

          bool     CanSpecial() { return GetWeapons().GetSpecialGauge() > 0.2; }
          virtual void Hit(CProjectile &proj, CScreenPos pos,
                           float dt) override;
          virtual void UseSpecial(float dt) override;
          virtual void UseSuper(float dt, bool use = true) override;
          virtual void UseWeapon(float dt) override;

private:

  CMoverObj *mDeflector;

  bool IsWithinCone(const CVector2& pos) const;

};


#endif
