#include "CBoomerang.hpp"
#include "CNose.hpp"
#include "CScramble.hpp"
#include "CInvulnerable.hpp"
#include "CShip.hpp"


CBoomerang::CBoomerang(const CProjBluePrint &bluePrint, CShip& ship,
		       const CVector2& pos, const CVector2& vel, bool shadow):
  CProjectile(bluePrint, ship, pos, vel, shadow) {

}


void CBoomerang::Move(float dt) {
 CProjectile::Move(dt);
 if(!IsStopped()) mNose = (mNose + 1) % CNose::kNbNoses;
}


void CBoomerang::HitShipEffect(CShip& ship, CScreenPos pos, float dt) {
  if(!ship.IsEffectOn(CScramble::GetID()) &&
     !ship.IsEffectOn(CInvulnerable::GetID())) //not a cumulative effect
    ship.StartEffect(CScramble::GetID());
}
