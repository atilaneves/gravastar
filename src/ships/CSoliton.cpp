#include "CSoliton.hpp"
#include "CShipFactory.hpp"
#include "CProjLauncher.hpp"
#include "CNose.hpp"
#include "CGravityProj.hpp"
#include "CShips.hpp"
#include "CShipBluePrint.hpp"
#include "CShipSounds.hpp"
#include "CSpecialExplosion.hpp"
#include "CProjectiles.hpp"
#include <math.h>


static std::string gShotName = "miniBullet2";
REG_PROJ_SHIP("Soliton", CSoliton, gShotName, gShotName, CProjectile,
	      CProjSpecial)
REG_WEAPON_PROJ(gShotName, CGravityProj)


CSoliton::CSoliton(const CShipBluePrint& bluePrint, CPilot& pilot,
		   CLevel &level):
  CShip(bluePrint, pilot, level),
  mShockwave(bluePrint.mSounds.mShockwave),
  mSpecialExpSprites(bluePrint.mSpecialExpSprites) {

}


void CSoliton::UseWeapon(float dt) {
  float da1 = 0.3; //small variation in angle
  float da2 = 1; //small variation in angle
  float dist1 = 0.5;
  float dist2 = 0.45;
  SpawnShot(dt, dist1, da1);
  SpawnShot(dt, dist1, -da1);
  SpawnShot(dt, dist2, da2);  //the 3 shots
  SpawnShot(dt, dist2, -da2);  //the 3 shots
}


void CSoliton::SpawnShot(float dt, float dist, float dAngle) {

  const float velNorm = 350;
  CVector2 vel = CProjLauncher::GetLaunchVel(*this, velNorm) + mVel / 2;
  CVector2 pos = CProjLauncher::GetLaunchPos(mWeapons.GetSpecialSprite(), dt,
					     *this, dist, dAngle);
  mWeapons.UseWeaponAt(pos, vel, gShotName);
}


static const float kScale = 100;
void CSoliton::UseSpecial(float dt) {
  float force = 500;
  CShips::PushAll(mPos, force, this, GetPilot());
  CProjectiles::DamageAll(mPos, force / kScale);
  new CSpecialExplosion(mLevel, mPos, mSpecialExpSprites, mShockwave, *this);
}


void CSoliton::UseSuper(float dt, bool use) {
  float force = 1250;
  CShips::PushAll(mPos, force, this, GetPilot(), 12.5);
  CProjectiles::DamageAll(mPos, force / kScale);
  mShockwave.Play(mPos);
  mShockwave.Play(mPos);
  mShockwave.Play(mPos);
  new CSpecialExplosion(mLevel, mPos, mSpecialExpSprites, mShockwave, *this);
}
