#include "CShipAura.hpp"
#include "CGravSprite.hpp"
#include "CFlicker.hpp"
#include "CFollower.hpp"
#include "CShip.hpp"
#include "CNose.hpp"
#include "CShipBluePrint.hpp"
#include "CWeapons.hpp"
#include "CTimeCounter.hpp"
#include "CSpriteObjs.hpp"

CShipAura::CShipAura(CLevel &level, CShip &ship,
                     const CShipBluePrint &bluePrint)
    : mRepairing(false), mBaseHull(bluePrint.mBaseHull),
      mBaseSpecial(bluePrint.mBaseSpecial), mLevel(level), mShip(ship),
      mSprites(CNose::kNbNoses, &bluePrint.mAuraSprite),
      mSound(bluePrint.mSounds.mRepairSound), mAura(nullptr) {}

void CShipAura::Repair(float dt) {
  if(mShip.GetHull() < mShip.GetMaxHull() ||
     (!mShip.GetWeapons().IsAtMax() && mBaseSpecial < 0.01))
    mRepairing = true;
  mShip.LoseHull(-mBaseHull * dt, mShip.GetPilot());
  mShip.GetWeapons().AddSpecialGauge(mBaseSpecial * dt);
}


void CShipAura::Update() {

  const float kAuraHz = 50;
  static CTimeCounter counter;

  if(mRepairing && !counter.IsActive()) {
    mSound.Play(mShip.GetPos());
    counter.Start(0.4);
  }

  if(mRepairing && !CSpriteObjs::HasFlicker(mAura)) {
    mAura = new CFlicker(kAuraHz, mLevel,
			 new CFollower(mSprites, mLevel, mShip));
  }
  else if(CSpriteObjs::HasFlicker(mAura) &&
	  (!mRepairing || !mShip.IsAlive())) {
    mAura->Die();
    mAura = nullptr;
  }

  mRepairing = false;
}


void CShipAura::Play() {
  mSound.Play(mShip.GetPos());
}
