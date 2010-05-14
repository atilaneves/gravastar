#ifndef CTEMPUS_H
#define CTEMPUS_H


#include "CShip.hpp"


class CTempus: public CShip {

public:

  CTempus(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level);

  virtual void    ApplyInput(const CPilotInput &controls);
  const CVector2& GetSpecialPos() const;
          bool    IsSpecialActive() const;
  virtual void    UseSpecial(float dt);
  virtual void    UseSuper(float dt, bool use = true);
  virtual void    UseWeapon(float dt);


private:

  bool mButton;
  CMoverObj* mBomb;

  void SpawnShot(float dt, float dAngle, float dVelAngle);
  void SpawnMissile(float dt, float velAngle, bool shadow = false);

};


#endif
