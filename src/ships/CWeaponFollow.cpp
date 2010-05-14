#include "CWeaponFollow.hpp"
#include "CProjectile.hpp"
#include "CShip.hpp"



CWeaponFollow::CWeaponFollow(const CSpriteVector &sprites, CLevel &level,
			     CMoverObj &obj, CSound *sound,
			     const CVector2& offset):
  CFollower(sprites, level, obj, sound, offset),
  mDamage(0) {

}


void CWeaponFollow::Hit(CSpriteObj& obj, CScreenPos pos, float dt) {
  CProjectile *proj = dynamic_cast<CProjectile*>(&obj);
  CShip       *ship = dynamic_cast<CShip*>(&obj);
  if(proj) Hit(*proj, pos, dt);
  if(ship && ship != &mFollowed) Hit(*ship, pos, dt);
}


void CWeaponFollow::Hit(CProjectile& proj, CScreenPos pos, float dt) {
  proj.LoseHull(2.25*mDamage * dt);
}


void CWeaponFollow::Hit(CShip& ship, CScreenPos pos, float dt) {
  CShip *myShip = (CShip*)&mFollowed;
  ship.LoseHull(mDamage * dt, myShip->GetPilot());
}


void CWeaponFollow::Move(float dt) { 
  CFollower::Move(dt);
  CheckCollision(dt);
}


void CWeaponFollow::HitTerrain(const CScreenPos &where, float dt) {
  mFollowed.SetVel(mFollowed.GetVel() * 0.75);
}
