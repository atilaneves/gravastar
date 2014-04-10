#include "CVulcan.hpp"
#include "CShipFactory.hpp"
#include "CHomingMissile.hpp"
#include "CProjLauncher.hpp"
#include "CNose.hpp"
#include "CGravityProj.hpp"
#include "CSpriteObjs.hpp"
#include "CPilotInput.hpp"
#include <math.h>


static std::string gMissName = "cluster";
static std::string gShotName = "lavaMedium";
REG_PROJ_SHIP("Vulcan", CVulcan, gShotName, gMissName, CGravityProj,
              CProjSpecial)
REG_EXTRA_BLUEPRINT("Vulcan", "clusterSpawn")

CVulcan::CVulcan(const CShipBluePrint &bluePrint, CPilot &pilot, CLevel &level)
    : CShip(bluePrint, pilot, level), mReleasedCluster(true),
      mReleasedSpawn(true), mCluster(nullptr) {}

void CVulcan::UseWeapon(float dt) {
  const float dist = 0.6, velNorm = 375;
  CVector2 vel = CProjLauncher::GetLaunchVel(*this, velNorm);
  CVector2 pos = CProjLauncher::GetLaunchPos(mWeapons.GetWeaponSprite(), dt,
                                             *this, dist);
  mWeapons.UseWeaponAt(pos, vel, gShotName);
}


void CVulcan::UseSpecial(float dt) {
  if(mReleasedSpawn && !IsSpecialActive())
    LaunchCluster(dt);
  else
    mWeapons.LoseGauge(-1); //put it back, spawning instead
}


void CVulcan::LaunchCluster(float dt) {
  const float dist = -0.6, velNorm = 125;
  CVector2 vel = CProjLauncher::GetLaunchVel(*this, velNorm, M_PI);
  CVector2 pos = CProjLauncher::GetLaunchPos(mWeapons.GetSpecialSprite(), dt,
                                             *this, dist);
  bool shadow = false;
  mCluster = mWeapons.UseSpecialAt(pos, vel, gMissName, shadow);
  mReleasedCluster = false;
  mReleasedSpawn   = true;
}


void CVulcan::ApplyInput(const CPilotInput &controls) {
  CShip::ApplyInput(controls);
  if(mReleasedCluster && controls.Special() && IsSpecialActive())
    LaunchSpawn();

  if(mReleasedCluster && !controls.Special()) mReleasedSpawn   = true;
  if(mReleasedSpawn   && !controls.Special()) mReleasedCluster = true;
}


void CVulcan::LaunchSpawn() {
  for(float angle = 0; angle < 2*M_PI; angle += M_PI/4) {
    CVector2 pos = mCluster->GetPos() + CVector2(angle) * 10;
    CVector2 vel = mCluster->GetVel() + CVector2(angle) * 30;
    new CGravityProj(mExtraProjBluePrint, *this, pos, vel);
  }
  CSpriteObjs::RemoveObj(mCluster);
  delete mCluster;
  mCluster = nullptr;
  mReleasedCluster = true;
  mReleasedSpawn   = false;
}


void CVulcan::UseSuper(float dt, bool use) {

  const float dist = 0.6;
  const float velNorm = 150 + (rand()/float(RAND_MAX)) * 200;
  const float velAngle = CNose::NoseIndex2Angle(GetNose());
  const float spread = 0.3;
  const float dAngle = (rand()/(float)RAND_MAX) * 2 * spread - spread;
  CVector2 vel = CVector2(velAngle + dAngle) * velNorm;
  CVector2 pos = CProjLauncher::GetLaunchPos(mWeapons.GetSpecialSprite(), dt,
                                             *this, dist, dAngle);
  bool shadow = true;
  mWeapons.UseSpecialAt(pos, vel, gMissName, shadow);
}


const CVector2& CVulcan::GetSpecialPos() const {
  static CVector2 nowhere(0, 0);
  if(IsSpecialActive())
    return mCluster->GetPos();
  else
    return nowhere;
}


bool CVulcan::IsSpecialActive() const {
  CGravityProj *proj = mCluster && CSpriteObjs::HasObj(mCluster)
                           ? dynamic_cast<CGravityProj *>(mCluster)
                           : nullptr;
  return proj && fabs(proj->GetMaxDamage() - 10) < 1e-3;
}
