#include "CTempus.hpp"
#include "CShipFactory.hpp"
#include "CProjLauncher.hpp"
#include "CNose.hpp"
#include "CGravityProj.hpp"
#include "CStasisBomb.hpp"
#include "CSpriteObjs.hpp"
#include "CPilotInput.hpp"
#include <math.h>


static std::string gMissName = "stasisBomb";
static std::string gShotName = "shot";
REG_PROJ_SHIP("Tempus", CTempus, gShotName, gMissName, CStasisBomb,
              CProjSpecial)
REG_WEAPON_PROJ(gShotName, CGravityProj)

CTempus::CTempus(const CShipBluePrint &bluePrint, CPilot &pilot, CLevel &level)
    : CShip(bluePrint, pilot, level), mButton(false), mBomb(nullptr) {}

void CTempus::UseWeapon(float dt) {
  float da  = 0.75;  //small variation in angle
  float dv1 = 0.35;
  float dv2 = 0.2;
  SpawnShot(dt, -da,  dv1);
  SpawnShot(dt,  da, -dv1);
  SpawnShot(dt, -da,  dv2);
  SpawnShot(dt,  da,  -dv2);
}


void CTempus::SpawnShot(float dt, float dAngle, float dVelAngle) {
  const double dist = 1, velNorm = 200;
  CVector2 vel = CProjLauncher::GetLaunchVel(*this, velNorm, dVelAngle) + mVel;
  CVector2 pos = CProjLauncher::GetLaunchPos(mWeapons.GetSpecialSprite(), dt,
                                             *this, dist, dAngle);
  mWeapons.UseWeaponAt(pos, vel, gShotName);
}



void CTempus::UseSpecial(float dt) {
  if(!mButton) SpawnMissile(dt, 0);
}


void CTempus::UseSuper(float dt, bool use) {
  const float maxTime = 15;
  CSpriteObjs::Stop(mPos, *this, maxTime);
}


void CTempus::SpawnMissile(float dt, float dAngle, bool shadow) {
  const float dist = 0.75, velNorm = 300;
  CVector2 vel = CProjLauncher::GetLaunchVel(*this, velNorm, dAngle);
  CVector2 pos = CProjLauncher::GetLaunchPos(mWeapons.GetSpecialSprite(), dt,
                                             *this, dist, dAngle);
  mBomb = mWeapons.UseSpecialAt(pos, vel, gMissName, shadow);
  mButton = true;
}


void CTempus::ApplyInput(const CPilotInput &controls) {
  if(!controls.Special()) mButton = false;
  if(controls.Special() && !mButton && IsSpecialActive()) {
    mBomb->Die();
    mBomb = nullptr;
    mButton = true;
  }
  CShip::ApplyInput(controls);
}


const CVector2& CTempus::GetSpecialPos() const {
  return mBomb->GetPos();
}


bool CTempus::IsSpecialActive() const {
  return mBomb && CSpriteObjs::HasObj(mBomb) &&
    dynamic_cast<CStasisBomb*>(mBomb);
}
