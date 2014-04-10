#include "CNimbus.hpp"
#include "CShipFactory.hpp"
#include "CProjLauncher.hpp"
#include "CNose.hpp"
#include "CGravityProj.hpp"
#include "CStealthMine.hpp"
#include <math.h>


static std::string gMissName = "stealthMine";
static std::string gShotName = "shot";
REG_PROJ_SHIP("Nimbus", CNimbus, gShotName, gMissName, CStealthMine,
              CProjSpecial)
REG_WEAPON_PROJ(gShotName, CGravityProj)


CNimbus::CNimbus(const CShipBluePrint& bluePrint, CPilot& pilot,
                 CLevel &level):
    CShip(bluePrint, pilot, level) {

}


void CNimbus::UseWeapon(float dt) {
  float da = M_PI / 15; //small variation in angle
  SpawnShot(dt, -da);
  SpawnShot(dt, da);
  SpawnShot(dt, -2*da);
  SpawnShot(dt, 2*da);
}


void CNimbus::SpawnShot(float dt, float dAngle) {
  const double dist = 0.65, velNorm = 300;
  CVector2 vel = CProjLauncher::GetLaunchVel(*this, velNorm) + mVel;
  CVector2 pos = CProjLauncher::GetLaunchPos(mWeapons.GetSpecialSprite(), dt,
                                             *this, dist, dAngle);
  mWeapons.UseWeaponAt(pos, vel, gShotName);
}



void CNimbus::UseSpecial(float dt) {
  const float dist = -1, velNorm = -100;
  CVector2 vel = CProjLauncher::GetLaunchVel(*this, velNorm) + mVel;
  CVector2 pos = CProjLauncher::GetLaunchPos(mWeapons.GetSpecialSprite(), dt,
                                             *this, dist);
  bool shadow = false;
  mWeapons.UseSpecialAt(pos, vel, gMissName, shadow);
}


void CNimbus::UseSuper(float dt, bool use) {
  const float dist     = 1;
  const float velNorm  = 200 + (rand()/float(RAND_MAX)) * 350;
  const float velAngle = (rand()/float(RAND_MAX)) * 2 * M_PI;
  const float dAngle   = velAngle - CNose::NoseIndex2Angle(GetNose());
  CVector2 vel = CVector2(velAngle) * velNorm;
  CVector2 pos = CProjLauncher::GetLaunchPos(mWeapons.GetSpecialSprite(), dt,
                                             *this, dist, dAngle);
  bool shadow = false;
  mWeapons.UseSpecialAt(pos, vel, gMissName, shadow);
}
