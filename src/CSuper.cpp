#include "CSuper.hpp"
#include "CShip.hpp"
#include "CShipBluePrint.hpp"
#include "CSuperExplosion.hpp"
#include "CPilotInput.hpp"
#include "CSuperTimer.hpp"
#include "CVector2.hpp"
#include "CPilot.hpp"
#include "CPilots.hpp"
#include "CGravSprite.hpp"


CSuper::CSuper(const CShipBluePrint &bluePrint, CLevel &level, CShip &ship):
  mLevel(level), mShip(ship), mExpSprites(bluePrint.mSuperExpSprites),
  mSound(bluePrint.mSounds.mSuperSound),
  mExpSound(bluePrint.mSounds.mSuperExpSound),
  mRate(bluePrint.mSuperRate), mDuration(bluePrint.mSuperDuration),
  mGauge(0), mSprite(bluePrint.mSuperSprite) {

}


void CSuper::ApplyInput(const CPilotInput& input) {
  if(input.Super() && CanUse() && !mExpCounter.IsActive()) {
    new CSuperExplosion(mLevel, mShip.GetPos(), mExpSprites, mSound, mShip);
    mExpCounter.Start(0.5);
    mGauge = 0; //reset
  }
}


void CSuper::Update(float dt) {
  if(mExpCounter.JustFinished()) mSuperCounter.Start(mDuration);
  if(mSuperCounter.IsActive() &&
     CSuperTimer::Instance().IsReady(mShip.GetPilot().GetIndex(), mRate))
      mShip.UseSuper(dt, true);
  if(mSuperCounter.JustFinished()) mShip.UseSuper(dt, false);
}


void CSuper::AddGauge(float amount) {
  const float scale[] = { 1, 1, 1.175, 1.375 };
  bool hadSuper = CanUse();
  const float kSuperDamage = 40;
  mGauge += amount / (kSuperDamage * scale[CPilots::GetNbLivePilots()-1]);
  if(!hadSuper && CanUse()) mSound.Play(mShip.GetPos());
}


void CSuper::DrawStats(CCanvas& canvas) const {
  if(!CanUse()) return;
  constexpr int x = 67, y = 10;
  mSprite.Draw(canvas, x, y);
}
