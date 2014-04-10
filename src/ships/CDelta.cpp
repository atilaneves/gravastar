#include "CDelta.hpp"
#include "CShipFactory.hpp"
#include "CProjLauncher.hpp"
#include "CNose.hpp"
#include "CGravityProj.hpp"
#include <math.h>


static std::string gMissName = "missile";
static std::string gShotName = "shot";
REG_PROJ_SHIP("Delta", CDelta, gShotName, gMissName, CProjectile, CProjSpecial)
REG_WEAPON_PROJ(gShotName, CGravityProj)


CDelta::CDelta(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level):
    CShip(bluePrint, pilot, level) {

}


void CDelta::UseWeapon(float dt) {
  float da = M_PI / 16; //small variation in angle
  SpawnShot(dt, 0);
  SpawnShot(dt, -da);
  SpawnShot(dt, da);  //the 3 shots
}


void CDelta::SpawnShot(float dt, float dAngle) {

  const double dist = 0.65, velNorm = 200;
  CVector2 vel = CProjLauncher::GetLaunchVel(*this, velNorm, dAngle) + mVel;
  CVector2 pos = CProjLauncher::GetLaunchPos(mWeapons.GetSpecialSprite(), dt,
					     *this, dist, dAngle);
  mWeapons.UseWeaponAt(pos, vel, gShotName);
}



void CDelta::UseSpecial(float dt) {
  SpawnMissile(dt, 0);
}


void CDelta::UseSuper(float dt, bool use) {
  static int counter = 0; //which way we'll fire
  const float dAngle = 0.15; //radians
  const float angle = (counter%3 -1)*dAngle;
  const bool shadow = true;
  SpawnMissile(dt, angle, shadow);
  counter++; //sweep across cone
}


void CDelta::SpawnMissile(float dt, float dAngle, bool shadow) {
  const float dist = 0.75, velNorm = 500;
  CVector2 vel = CProjLauncher::GetLaunchVel(*this, velNorm, dAngle);
  CVector2 pos = CProjLauncher::GetLaunchPos(mWeapons.GetSpecialSprite(), dt,
					     *this, dist, dAngle);
  mWeapons.UseSpecialAt(pos, vel, gMissName, shadow);  
}
