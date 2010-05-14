#include "CShip.hpp"
#include "CShipBluePrint.hpp"
#include "CLevel.hpp"
#include "CShips.hpp"
#include "CProjectile.hpp"
#include "CInvulnerable.hpp"
#include "CEffectPush.hpp"
#include "CPilot.hpp"


CShip::CShip(const CShipBluePrint &bluePrint, CPilot& pilot, CLevel &level):
  CExplosive(bluePrint.mExplosiveBluePrint, level, pilot,
	     level.GetFreePos(bluePrint.GetSprite()), CVector2(0, 0),
	     bluePrint.mMaxHull),
  mEngine(bluePrint, level, *this), mNose(bluePrint, *this),
  mFriction(*this, level),
  mCollider(*this, level, bluePrint.mSounds.mKlangSound),
  mAura(level, *this, bluePrint), mSpawn(bluePrint.mSounds.mSpawnSound), 
  mInvSprites(bluePrint.mInvulnerableBluePrint.GetSprites()),
  mScrambleSprites(bluePrint.mScrambleBluePrint.GetSprites()),
  mEMPSprites(bluePrint.mEMPBluePrint.GetSprites()),
  mEffects(bluePrint.mTeam, *this, level),
  mWeapons(bluePrint.mName, bluePrint, *this, level),
  mExtraProjBluePrint(*bluePrint.mExtraProjBluePrint),
  mExtraFollowBluePrint(*bluePrint.mExtraFollowBluePrint) {

  mSpawn.Play(mPos);
  mMass    = bluePrint.mMass;
  mShockWaveForce = 300; //when we die we push ppl
  CShips::AddShip(this);
  mEffects.Start(CInvulnerable::GetID());
}


CShip::~CShip() {
  CShips::RemoveShip(this);
  mPilot.NextShip();
}


void CShip::ApplyInput(const CPilotInput &controls) {
  if(!IsAlive())  return;
  if(IsStopped()) return;
  mNose.ApplyInput(controls);
  mEngine.ApplyInput(controls);
  mWeapons.ApplyInput(controls);
}


void CShip::Move(float dt) {
  mEffects.Update();
  if(!IsAlive()) return;
  CExplosive::Move(dt);
  if(IsStopped()) return;
  mNose.Update(dt);
  mAura.Update();
  mWeapons.Update(dt);
  if(mWeapons.IsSuperActive() && !CanMoveSuper()) mVel = CVector2(0, 0);
}


CVector2 CShip::CalcAcc() {
  CVector2 acc(0, mLevel.GetGravity());
  acc += mEngine.CalcAcc(mNose.GetAngle());
  acc += mFriction.CalcAcc();
  return acc;
}


void CShip::Rebound(float angle, float r) {

 const float kLowSpeed = 3.75;
 r += 1.0;
 CVector2 toAdd(r * fabs(mVel.GetX()) * std::cos(angle),
		r * fabs(mVel.GetY()) * std::sin(angle));
 mVel += toAdd;

 if(mVel.GetY() < kLowSpeed && std::sin(angle) > 0)
   mVel.SetY(0); //stops jitter
}


void CShip::Hit(CShip& ship, CScreenPos pos, float dt) {
  mCollider.Hit(ship, dt);
}


void CShip::Hit(CProjectile& proj, CScreenPos pos, float dt) {
  proj.Hit(*this, pos, dt);
}


void CShip::HitTerrain(const CScreenPos &where, float dt) {

  float edgeAngle;
  bool landed = mCollider.BouncedOff(where, edgeAngle);

  if(landed)
    BounceOff(edgeAngle, dt);
  else {
    mFriction.SetInTerrain();
    LandDamage(dt);
  }
}


void CShip::BounceOff(float edgeAngle, float dt) {
  BackTrack(dt);
  Rebound(edgeAngle);
  mVel += mCollider.VelAfterFriction(edgeAngle, GetVel());
}


void CShip::PullBack(const CSpriteObj& obj, float angle) {
  CVector2 deltaS(angle);
  CVector2 pos = mPos;
  const float kMaxDist = 200;
  while(Collided(obj) && (mPos - pos).Radius() < kMaxDist) {
    if(mPos.GetX() < 0 || mPos.GetX() >= mLevel.GetWidth() ||
       mPos.GetY() < 0 || mPos.GetY() >= mLevel.GetHeight())
      Die();
    mPos += deltaS;
  }
}


void CShip::AtDeath() {
  CExplosive::AtDeath();
  mEngine.Reset(); //no thrust whilst we're dead and waiting
  if(!mEffects.JustFinished(CExplosionPause::GetID()))
    mEffects.Start(CExplosionPause::GetID()); //lil pause then we're back
}


void CShip::Push(const CVector2 &speed, CPilot &pilot) {
  if(IsEffectOn(CInvulnerable::GetID())) return;
  if(GetWeapons().IsSuperActive()) return;
  CVector2 force = speed * 1/mMass;
  mVel += force;
  mNose.Spin(force);
  if(force.Radius() > 100 &&
     GetPilot().GetTeam() != pilot.GetTeam()) {
    mEffects.Start(CEffectPush::GetID());
    ((CEffectPush*)mEffects.GetEffect(CEffectPush::GetID()))->
      SetPilot(pilot);
  }
}


void CShip::LoseHull(float amount, CPilot &pilot) {
  if(IsEffectOn(CInvulnerable::GetID())) return;
  int oldHull = int(mHull);
  CExplosive::LoseHull(amount);
  if(oldHull < int(mHull)) mAura.Play();
  if(amount > 0) pilot.AddDamage(amount, GetPilot());
  if(!IsAlive()) pilot.AddFrag(GetPilot());
}
