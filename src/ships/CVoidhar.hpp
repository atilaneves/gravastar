#ifndef CVOIDHAR_H
#define CVOIDHAR_H


#include "CShip.hpp"
#include "CSpriteVector.hpp"
class CFlicker;


class CVoidhar: public CShip {

public:

  CVoidhar(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level);

  virtual void UseSpecial(float dt) override;
  virtual void UseSuper(float dt, bool use = true) override;
  virtual void UseWeapon(float dt) override;

private:

  CSound mEMP;
  CSpriteVector mSpecialExpSprites;

};


#endif
