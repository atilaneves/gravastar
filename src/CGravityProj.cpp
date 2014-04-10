#include "CGravityProj.hpp"
#include "CLevel.hpp"


CGravityProj::CGravityProj(const CProjBluePrint &bluePrint, CShip& ship,
			   const CVector2& pos, const CVector2& vel,
			   bool shadow):
  CProjectile(bluePrint, ship, pos, vel, shadow) {

}


CVector2 CGravityProj::CalcAcc() {
  const float scale = 0.33;
  return (scale * mVel * -mLevel.GetAirFriction())/mMass + //friction
         CVector2(0, mLevel.GetGravity()); //gravity
}
