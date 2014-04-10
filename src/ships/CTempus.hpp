#ifndef CTEMPUS_H
#define CTEMPUS_H


#include "CShip.hpp"


class CTempus: public CShip {

public:

  CTempus(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level);

  virtual void ApplyInput(const CPilotInput &controls) override;
  const CVector2& GetSpecialPos() const;
          bool    IsSpecialActive() const;
          virtual void UseSpecial(float dt) override;
          virtual void UseSuper(float dt, bool use = true) override;
          virtual void UseWeapon(float dt) override;

private:

  bool mButton;
  CMoverObj* mBomb;

  void SpawnShot(float dt, float dAngle, float dVelAngle);
  void SpawnMissile(float dt, float velAngle, bool shadow = false);

};


#endif
