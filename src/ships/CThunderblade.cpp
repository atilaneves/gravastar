#include "CThunderblade.hpp"
#include "CShipFactory.hpp"
#include "CProjLauncher.hpp"
#include "CNose.hpp"
#include "CLevel.hpp"
#include "CLightning.hpp"
#include "CFlicker.hpp"
#include "CThrustUp.hpp"
#include "CSpriteObjs.hpp"
#include <math.h>

static std::string gShipName = "Thunderblade";
static std::string gFollowName = "lightning";
static std::string gShotName = "bullet";
static std::string gSuperName = "tempest";

REG_FOLLOW_SHIP(gShipName, CThunderblade, gShotName, gFollowName,
                CLightning, CFollowSpecial)
REG_EXTRA_FOLLOW_BLUEPRINT("Thunderblade", gSuperName)
REG_EXTRA_FOLLOW(gSuperName, CWeaponFollow)



CThunderblade::CThunderblade(const CShipBluePrint& bluePrint,
			     CPilot& pilot, CLevel &level):
    CShip(bluePrint, pilot, level),
    mTempest(0) {

}


void CThunderblade::UseWeapon(float dt) {
  float dPosAngle = 1.5; //small variation in angle
  float dVelAngle = 0.075;
  SpawnBullet(dt, -dPosAngle, dVelAngle);
  SpawnBullet(dt, dPosAngle, -dVelAngle);
}


void CThunderblade::SpawnBullet(float dt, float dAngle, float dVelAngle) {
  CVector2 pos = CProjLauncher::GetLaunchPos(mWeapons.GetWeaponSprite(), dt,
					     *this, 0.55, dAngle);
  CVector2 vel = CProjLauncher::GetLaunchVel(*this, 600, dVelAngle);
  mWeapons.UseWeaponAt(pos, vel, gShotName);
}



void CThunderblade::UseSpecial(float dt) {
  mWeapons.UseSpecialAt(mPos, mVel, gFollowName);
}


void CThunderblade::UseSuper(float dt, bool use) {
  if(!use && mTempest) {
    mTempest->Die();
    mTempest = 0;
  }
  else if (use && !mTempest) {
    static CSound sound = mExtraFollowBluePrint.GetSound();
    const CVector2 offset(0, 0);
    const CSpriteVector &sprites = mExtraFollowBluePrint.GetSprites();
    const float kFrequency = 70;
    mTempest = new CWeaponFollow(sprites, mLevel, *this, 0, offset);
    mTempest->SetDamage(75);
    new CFlicker(kFrequency, mLevel, mTempest);
    mEffects.Start(CThrustUp::GetID(), 4);
  }
}
