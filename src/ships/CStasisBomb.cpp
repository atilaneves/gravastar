#include "CStasisBomb.hpp"
#include "CSpriteObjs.hpp"
#include "CPilot.hpp"
#include "CShip.hpp"


CStasisBomb::CStasisBomb(const CProjBluePrint &bluePrint, CShip& ship,
		       const CVector2& pos, const CVector2& vel, bool shadow):
  CProjectile(bluePrint, ship, pos, vel, shadow) {

}



void CStasisBomb::AtDeath() {
  float maxTime = 1;
  CSpriteObjs::Stop(mPos, mPilot.GetShip(), maxTime);
  CProjectile::AtDeath();
}
