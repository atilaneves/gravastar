#ifndef CSOLITON_H
#define CSOLITON_H


#include "CShip.hpp"
#include "CSpriteVector.hpp"


class CSoliton: public CShip {

public:

  CSoliton(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level);

  virtual void UseSpecial(float dt);
  virtual void UseSuper(float dt, bool use = true);
  virtual void UseWeapon(float dt);


private:

  CSound mShockwave;
  CSpriteVector mSpecialExpSprites;

  void SpawnShot(float dt, float dist, float dAngle);

};


#endif
