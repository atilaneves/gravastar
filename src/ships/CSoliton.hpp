#ifndef CSOLITON_H
#define CSOLITON_H


#include "CShip.hpp"
#include "CSpriteVector.hpp"


class CSoliton: public CShip {

public:

  CSoliton(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level);

  virtual void UseSpecial(float dt) override;
  virtual void UseSuper(float dt, bool use = true) override;
  virtual void UseWeapon(float dt) override;

private:

  CSound mShockwave;
  CSpriteVector mSpecialExpSprites;

  void SpawnShot(float dt, float dist, float dAngle);

};


#endif
