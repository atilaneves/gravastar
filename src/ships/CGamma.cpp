#include "CGamma.hpp"
#include "CShipFactory.hpp"
#include "CProjLauncher.hpp"
#include "CNose.hpp"
#include "CGravityProj.hpp"
#include "CLevel.hpp"
#include "CShips.hpp"
#include "CSpriteObjs.hpp"
#include "CProjectile.hpp"
#include "CPulseLaser.hpp"
#include "CSuperBeam.hpp"
#include "CFlicker.hpp"
#include "CFollower.hpp"
#include "CShipBluePrint.hpp"
#include "CShipSounds.hpp"
#include <math.h>


static std::string gShipName = "Gamma";
static std::string gMissName = "pulseLaser";
static std::string gShotName = "shot";
static std::string gSuperName = "superBeam";
REG_PROJ_SHIP(gShipName, CGamma, gShotName, gMissName, CPulseLaser,
	      CProjSpecial)
REG_WEAPON_PROJ(gShotName, CGravityProj)
REG_EXTRA_FOLLOW_BLUEPRINT(gShipName, gSuperName)


CGamma::CGamma(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level):
    CShip(bluePrint, pilot, level),
    mAngle(0), mDirection(0.05), mSuperBeam(0), mPulse(0),
    mSuperBeamSound(bluePrint.mSounds.mSuperBeamSound) {

}


CGamma::~CGamma() {
  mSuperBeamSound.Stop();
}


void CGamma::UseWeapon(float dt) {
  const float kMaxAngle = 0.275;
  if(fabs(mAngle) > kMaxAngle) mDirection *= -1;
  mAngle += mDirection;
  const double dist = 0.7, velNorm = 200;
  CVector2 vel = CProjLauncher::GetLaunchVel(*this, velNorm, mAngle) + mVel;
  CVector2 pos = CProjLauncher::GetLaunchPos(mWeapons.GetSpecialSprite(), dt,
					     *this, dist, mAngle);
  mWeapons.UseWeaponAt(pos, vel, gShotName);
}


void CGamma::UseSpecial(float dt) {
  if(IsSpecialActive()) return;
  CVector2 vel = CVector2(mNose.GetAngle()) * 1e-6;
  bool shadow = false;
  mPulse = mWeapons.UseSpecialAt(mPos, vel, gMissName, shadow);
}


void CGamma::UseSuper(float dt, bool use) {
  if(!use && mSuperBeam) {
    mSuperBeam->Die();
    mSuperBeam = 0;
    mSuperBeamSound.Stop();
  }
  else if(use && !mSuperBeam) {
    const CSpriteVector &sprites = mExtraFollowBluePrint.GetSprites();
    const float kFrequency = 70;
    mSuperBeam = new CSuperBeam(sprites, mLevel, *this);
    new CFlicker(kFrequency, mLevel, mSuperBeam);
    float volume = 1;
    bool loop = true;
    mSuperBeamSound.Play(mPos, volume, loop);
  }
  else if(use && mSuperBeam) {
    mSuperBeam->Move(dt);    
  }
}


bool CGamma::IsSpecialActive() const {
  return CSpriteObjs::HasObj(mPulse) && dynamic_cast<CPulseLaser*>(mPulse);
}
