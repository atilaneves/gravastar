#ifndef CPHANTOM_H
#define CPHANTOM_H


#include "CShip.hpp"
#include "CTimeCounter.hpp"


class CPhantom: public CShip {

public:

  CPhantom(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level);

  virtual void ApplyInput(const CPilotInput &controls);
          bool CanPhase();
  virtual void Draw();
  virtual bool IsAlive() { return CShip::IsAlive() && !mPhased; }
  virtual void Update(float dt);
  virtual void UseSpecial(float dt);
  virtual void UseSuper(float dt, bool use = true);
  virtual void UseWeapon(float dt);


private:

  bool   mPhased;
  bool   mHisteresis;
  CSound mFlashForward;
  CTimeCounter mPhaseCounter;

  void SpawnShot(float dt, float dAngle);

};


#endif
