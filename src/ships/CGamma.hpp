#ifndef CGAMMA_H
#define CGAMMA_H


#include "CShip.hpp"
class CSuperBeam;


class CGamma: public CShip {

public:

  CGamma(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level);
  virtual ~CGamma();

          bool IsSpecialActive() const;
          virtual void UseSpecial(float dt) override;
          virtual void UseSuper(float dt, bool use = true) override;
          virtual void UseWeapon(float dt) override;

private:

  float mAngle;
  float mDirection;
  CSuperBeam *mSuperBeam;
  CMoverObj  *mPulse;
  CSound      mSuperBeamSound;

};


#endif
