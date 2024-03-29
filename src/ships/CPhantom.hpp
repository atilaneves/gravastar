#ifndef CPHANTOM_H
#define CPHANTOM_H


#include "CShip.hpp"
#include "CTimeCounter.hpp"


class CPhantom: public CShip {

public:

  CPhantom(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level);

  virtual void ApplyInput(const CPilotInput &controls) override;
          bool CanPhase();
  virtual CLevelSprite Draw() override;
  virtual bool IsAlive() override { return CShip::IsAlive() && !mPhased; }
  virtual void Update(float dt) override;
  virtual void UseSpecial(float dt) override;
  virtual void UseSuper(float dt, bool use = true) override;
  virtual void UseWeapon(float dt) override;

private:

  bool   mPhased;
  bool   mHisteresis;
  CSound mFlashForward;
  CTimeCounter mPhaseCounter;

  void SpawnShot(float dt, float dAngle);

};


#endif
