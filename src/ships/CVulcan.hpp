#ifndef CVULCAN_H
#define CVULCAN_H


#include "CShip.hpp"


class CVulcan: public CShip {

public:

  CVulcan(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level);

  virtual void ApplyInput(const CPilotInput &controls) override;
  const CVector2& GetSpecialPos() const;
  bool IsSpecialActive() const;
  virtual void UseSpecial(float dt) override;
  virtual void UseSuper(float dt, bool use = true) override;
  virtual void UseWeapon(float dt) override;

private:

  bool mReleasedCluster;
  bool mReleasedSpawn;
  CMoverObj *mCluster;

  void LaunchCluster(float dt);
  void LaunchSpawn();
};


#endif
