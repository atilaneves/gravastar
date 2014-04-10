#include "CShipCollider.hpp"
#include "CShip.hpp"
#include "CLevel.hpp"
#include "CColour.hpp"
#include "CNose.hpp"
#include "CPilot.hpp"
#include "CInvulnerable.hpp"
#include "CEffectPush.hpp"
#include <math.h>


extern bool gDebug;


CShipCollider::CShipCollider(CShip &ship, CLevel& level, const CSound &klang):
  mShip(ship), mLevel(level), mKlang(klang) {

}


bool CShipCollider::BouncedOff(const CScreenPos& pos, float &edgeAngle) {

  edgeAngle = mLevel.FindEdge(pos);
  const int   kNoseIndex = CNose::Angle2NoseIndex(edgeAngle);
  const int   kInterval  = kNoseIndex == CNose::kNbNoses/4 ? 2 : 1;
  const int   kNose1     = kNoseIndex - kInterval;
  const int   kNose2     = kNoseIndex + kInterval;
  int spriteIndex = mShip.GetSpriteIndex();
  if(kNose1 < 0 && spriteIndex > CNose::kNbNoses/2)
    spriteIndex -= CNose::kNbNoses; //360º back
  const float kDot = mShip.GetVel() * CVector2(edgeAngle);
  //dot will be < 0 if we're going towards the edge
  if(kDot < 0 && spriteIndex >= kNose1 && spriteIndex <= kNose2) {
    mShip.mNose.Set(kNoseIndex + 0.1); //crashes if 0
    return true;
  }
  else
    return false;
}


CVector2 CShipCollider::VelAfterFriction(float angle,
                                         const CVector2& vel) const {
  const float f = 0.4;
  return CVector2((f-1) * vel.GetX() * fabs(sin(angle)),
                  (f-1) * vel.GetY() * fabs(cos(angle)));
}


void CShipCollider::Klang() {
  mKlang.Play(mShip.GetPos());
}


void CShipCollider::LandDamage(float dt) const {
  if(!mShip.IsEffectOn(CInvulnerable::GetID())) {
    const float kDamageFactor = 0.00067;
    const float kMinDamage = 6 * dt;
    const float kMaxDamage = 10;
    float damage = kDamageFactor * dt * mShip.GetVel().Radius2();
    if(damage < kMinDamage) damage = kMinDamage;
    if(damage > kMaxDamage) damage = kMaxDamage;
    mShip.LoseHull(damage, mShip.GetPilot()); //do the deed
    if(!mShip.IsAlive() && mShip.IsEffectOn(CEffectPush::GetID())) {
      CPilot &pilot=((CEffectPush*)mShip.mEffects.
                     GetEffect(CEffectPush::GetID()))->GetPilot();
      pilot.AddFrag(mShip.GetPilot());
      pilot.AddDamage(damage, mShip.GetPilot());
    }
  }
}


void calcV1V2(float m1, float m2, float u1, float u2, float &v1, float &v2) {
  v1 = (u1 * (m1 - m2) + 2 * m2 * u2) / (m1 + m2);
  v2 = (u2 * (m2 - m1) + 2 * m1 * u1) / (m1 + m2);
}


void calcV1V2Ship(CShip& mShip, CShip &ship, float &v1, float &v2) {
  calcV1V2(mShip.GetMass(), ship.GetMass(), mShip.GetVel().Radius(),
           ship.GetVel().Radius(), v1, v2);
}


void CShipCollider::Hit(CShip &ship, float dt) {
  //we've already been drawn, another ship hit us
  if(&ship == &mShip) return; //can't hit ourselves!
  bool towardsUs = (ship.GetPos() - mShip.GetPos()) * ship.GetVel() < 0;
  float pullAngle = towardsUs ? ship.mVel.Theta() + M_PI : ship.mVel.Theta();
  ship.PullBack(mShip, pullAngle); //get it out of our path
  //only if ship is moving towards us
  if(!towardsUs) return;
  float v1, v2;
  calcV1V2Ship(mShip, ship, v1, v2); //got the norms now
  CVector2 vel1 = CVector2(ship.GetVel().Theta()) * v1;
  CVector2 vel2 = CVector2(-ship.GetVel().Theta()) * v2;
  CVector2 dPos = ship.GetPos() - mShip.GetPos();

  if(vel1 * dPos > 0) {
    vel1 = CVector2(dPos.Theta()) * (-200 / 3);
    vel2 = vel1 * -1;
  }

  ship.mPos  += vel2 * dt;
  mShip.SetVel(vel1);
  ship.SetVel(vel2);

  mShip.mEffects.Start(CEffectPush::GetID());
    ((CEffectPush*)mShip.mEffects.GetEffect(CEffectPush::GetID()))->
      SetPilot(ship.GetPilot());

  ship.mEffects.Start(CEffectPush::GetID());
    ((CEffectPush*)ship.mEffects.GetEffect(CEffectPush::GetID()))->
      SetPilot(mShip.GetPilot());

  if(ship.GetVel().Radius2() > 10) mKlang.Play(mShip.GetPos());
}
