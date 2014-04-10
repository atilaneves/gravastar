#include "CHomingMissile.hpp"
#include "CShip.hpp"
#include "CPilots.hpp"
#include "CPilot.hpp"
#include <math.h>


CHomingMissile::CHomingMissile(const CProjBluePrint &bluePrint, CShip& ship,
			       const CVector2& pos, const CVector2& vel,
			       bool shadow):
  CProjectile(bluePrint, ship, pos, vel, shadow) {

}


void CHomingMissile::Move(float dt) {

  int targetIndex = GetTargetIndex();

  if(targetIndex != -1 && !IsStopped()) {

    CShip &ship   = CPilots::GetPilot(targetIndex).GetShip();
    CVector2 dist = ship.GetPos() - GetPos();
    float theta   = mVel.Theta();
    float dtheta  = dist.Theta() - theta;

    float kStepTheta = 1.5;
    
    if((dtheta > 0 && dtheta <= M_PI) ||
       (dtheta < 0 && dtheta <= -M_PI)) //adjust by a certain step
      theta += kStepTheta * dt;
    else if((dtheta < 0 && dtheta>=-M_PI) ||
	    (dtheta > 0 && dtheta>=M_PI)) //adjust by a certain step
      theta -= kStepTheta * dt;
    
    if(theta < 0)      theta += 2*M_PI;
    if(theta > 2*M_PI) theta -= 2*M_PI;
    
    mVel = mVel.Radius() * CVector2(theta);
    mNose = CNose::Angle2NoseIndex(theta);
  }

  CProjectile::Move(dt);
}


int CHomingMissile::GetTargetIndex() {
  //get nearest target in the forward cone
  int targetIndex = -1;
  float minDist2 = 9e9;

  for(int p = 0; p<CPilots::GetNbPilots(); p++) {
    CShip &ship = CPilots::GetPilot(p).GetShip();
      if(p != mPilot.GetIndex() && CPilots::GetPilot(p).IsAlive() &&
	 ship.IsAlive()) {

      CVector2 dist = ship.GetPos() - GetPos();
      float cosAngle = CVector2(dist.Theta()) * CVector2(mVel.Theta());
      const float kMaxCosAngle = 0.4; 
      if(cosAngle > kMaxCosAngle) { //forward cone
	float dist2 = dist.Radius2();
	if(dist2 < minDist2) {
	  targetIndex = p;
	  minDist2 = dist2;
	}
      }
    }
  }
  
  return targetIndex;
}
