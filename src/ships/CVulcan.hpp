#ifndef CVULCAN_H
#define CVULCAN_H


#include "CShip.hpp"


class CVulcan: public CShip {

public:

  CVulcan(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level);

  virtual void ApplyInput(const CPilotInput &controls);
  const CVector2& GetSpecialPos() const;
  bool IsSpecialActive() const;
  virtual void UseSpecial(float dt);
  virtual void UseSuper(float dt, bool use = true);
  virtual void UseWeapon(float dt);


private:

  bool mReleasedCluster;
  bool mReleasedSpawn;
  CMoverObj *mCluster;

  void LaunchCluster(float dt);
  void LaunchSpawn();
};


#endif
