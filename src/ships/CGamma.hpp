#ifndef CGAMMA_H
#define CGAMMA_H


#include "CShip.hpp"
class CSuperBeam;


class CGamma: public CShip {

public:

  CGamma(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level);
  virtual ~CGamma();

          bool IsSpecialActive() const;
  virtual void UseSpecial(float dt);
  virtual void UseSuper(float dt, bool use = true);
  virtual void UseWeapon(float dt);


private:

  float mAngle;
  float mDirection;
  CSuperBeam *mSuperBeam;
  CMoverObj  *mPulse;
  CSound      mSuperBeamSound;

};


#endif
