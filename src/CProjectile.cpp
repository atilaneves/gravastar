#include "CProjectile.hpp"
#include "CProjectiles.hpp"
#include "CProjBluePrint.hpp"
#include "CNose.hpp"
#include "CShip.hpp"
#include "CFollower.hpp"
#include "CFlicker.hpp"
#include "CInvulnerable.hpp"

#include "CPilot.hpp"
CProjectile::CProjectile(const CProjBluePrint &bluePrint, CShip &ship,
                         const CVector2 &pos, const CVector2 &vel, bool shadow)
    : CExplosive(bluePrint.mExplosiveBluePrint, ship.GetLevel(),
                 ship.GetPilot(), pos, vel, bluePrint.mMaxHull),
      mMaxDamage(bluePrint.mMaxDamage), mDamage(mMaxDamage),
      mNose(CNose::Angle2NoseIndex(vel.Theta())),
      mShadowSprites(bluePrint.mShadowBluePrint.GetSprites()),
      mHitObj(nullptr) {

  mMass = bluePrint.mMass;
  mShockWaveForce = bluePrint.mShockWaveForce;
  if(shadow) mShadowCounter.Start(0.15);
  CProjectiles::AddProjectile(this);
}


CProjectile::~CProjectile() {
  CProjectiles::RemoveProjectile(this);
}


void CProjectile::Update(float dt) {
  CExplosive::Update(dt);
  if(mShadowCounter.JustFinished()) CreateShadow();
}


void CProjectile::CreateShadow() {
  CSound *sound = nullptr;
  const float frequency = 50;
  CVector2 offset = CVector2(0) * GetHeight() * -1.75;
  new CFlicker(frequency, mLevel,
	       new CFollower(mShadowSprites, mLevel, *this, sound, offset));
}


void CProjectile::HitTerrain(const CScreenPos &where, float dt) {
  LoseHull(500*dt);
}


void CProjectile::Hit(CProjectile& proj, CScreenPos pos, float dt) {
  if(GetWidth() == 1 && proj.GetWidth() == 1) return; //shots
  float myDmg = mDamage, itsDmg = proj.mDamage; //might get changed below!
  proj.LoseHull(myDmg); //projectile gets hit
  LoseHull(itsDmg);     //we lose hull too!
}


void CProjectile::Hit(CShip& ship, CScreenPos pos, float dt) {

  if(&(ship.GetPilot()) == &mPilot && !WeShootOurOwn()) return;

  if(!ship.IsEffectOn(CInvulnerable::GetID())) { //if we can touch it
    HitShipEffect(ship, pos, dt);
    ship.LoseHull(mDamage, mPilot); //ship gets hit
  }

  mHitObj = &ship;
  Die(); //either way, we die
}


void CProjectile::Hit(CSpriteObj& sprObj, CScreenPos pos, float dt) {
 sprObj.Hit(*this, pos, dt);
}


void CProjectile::LoseHull(float amount) {
 CExplosive::LoseHull(amount);
 mDamage = mMaxDamage * (mHull/mMaxHull); //scale it
 if(mDamage < 0) mDamage = 0;
}


void CProjectile::HitShipEffect(CShip& ship, CScreenPos pos, float dt) {
  ship.Push(CVector2(mVel.Theta()) * mShockWaveForce, mPilot);
}


void CProjectile::SetVel(const CVector2& vel) {
  mVel = vel;
  mNose = CNose::Angle2NoseIndex(vel.Theta());
}
