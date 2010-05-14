#include "CSeekAndDestroy.hpp"
#include "CPilotBot.hpp"
#include "CPilots.hpp"
#include "CPoint2D.hpp"
#include "CAstar.hpp"
#include "CLevel.hpp"
#include "CPilotInputBot.hpp"
#include "CInvulnerable.hpp"
#include <math.h>
#include <algorithm>


CSeekAndDestroy::CSeekAndDestroy(CPilotBot &pilot):
   CBotAction(pilot),
   mPointAtTarget(false), mWait(false) {

}


void CSeekAndDestroy::Think() {

 mPointAtTarget = false; //reset
 CVector2 pos(0, 0);
 mTargetIndex = FindTarget(pos);
 mTargetAngle = FindTargetAngle(pos);
 if(mPointAtTarget)
    mNoseAngle = mTargetAngle;
 else
    SetNoseAngle();
}


int CSeekAndDestroy::FindTarget(CVector2& pos) {  //get nearest pilot

 int targetIndex = -1;
 float minDist2 = 9e9;
 CVector2 dist(0, 0);

 for(int s=0; s<CPilots::GetNbPilots(); s++) {

   if(!IsValidTarget(CPilots::GetPilot(s))) continue;
   dist = CPilots::GetPilot(s).GetShip().GetPos() - mPilot.GetShip().GetPos();

   if(dist.Radius2() < minDist2) {
     minDist2 = dist.Radius2();
     targetIndex = s;
    }
 }

 if(targetIndex >= 0)
   pos = SetNearestPoint(CPilots::GetPilot(targetIndex).GetShip().GetPos(),
			 dist.Theta());
 return targetIndex;
}


bool CSeekAndDestroy::IsValidTarget(const CPilot& pilot) {
  return pilot.IsAlive() && pilot.GetTeam() != mPilot.GetTeam() &&
         pilot.GetShip().IsAlive() && 
         (!pilot.GetShip().IsEffectOn(CInvulnerable::GetID()) ||
	  mPilot.GetShip().IsEffectOn(CInvulnerable::GetID()));
}


float CSeekAndDestroy::FindTargetAngle(const CVector2& pos) {

  CVector2 dist = pos - mPilot.GetShip().GetPos();
  float angle;
  
  if(!mPilot.IsClearLine(pos) &&
     !mPilot.GetShip().GetWeapons().IsSuperActive() ) {
    
    CPoint2D::SetStepSizes(mPilot.GetShip(), 25, 60);
    CAstar<CPoint2D> search(new CPoint2D(mPilot.GetShip().GetPos()),
			    new CPoint2D(pos));
    angle = CPoint2D::OpToAngle(search.Search());
  }
  else {
    angle = dist.Theta(); //clear shot, straight towards target
    mPointAtTarget=true;
  }
  
  if(angle < 0) angle += 2*M_PI; //guarantee it's in the [0,2pi[ interval
  return angle;
}


CVector2 CSeekAndDestroy::SetNearestPoint(const CVector2& pos, float pullAngle) {

  CVector2 newPos(pos); //save original coordinates
  int x0 = int(pos.GetX());    int y0 = int(pos.GetY());
  int x  = int(newPos.GetX()); int y  = int(newPos.GetY());
  if(mPilot.GetShip().GetLevel().IsFreeSquare(int(x), int(y))) return pos;
  
  const int stepSize = 20;
  const int r0 = (3*stepSize)/2; //initial r
  int r  = r0; //init it 
  const float deltaTheta = M_PI/4; //45 degrees, 8 directions
  
  while(true) {
    for(float theta = pullAngle;theta < pullAngle + 2*M_PI;theta+=deltaTheta) {
      newPos += CVector2(theta) * r;
      int x = int(newPos.GetX()); int y = int(newPos.GetY());
      if(x >= 0 && x < mPilot.GetShip().GetLevel().GetWidth() && 
	 y >= 0 && y < mPilot.GetShip().GetLevel().GetHeight() &&
	 mPilot.GetShip().GetLevel().IsFreeSquare(x, y) &&
	 (r > r0 || mPilot.GetShip().GetLevel().IsClearLine(x, y, x0, y0)))
	return newPos; //found a place to go to
    }
    r += stepSize; //increment radius of circle, chk again
  }
}


void CSeekAndDestroy::SetShootControl(CPilotInputBot &input) {
  if(mPilot.GetShip().GetWeapons().CanSuper())
    input.SetSuper();
  else if(mPilot.GetShip().GetWeapons().CanSpecial())
    input.SetSpecial();
  else if(!IsTooHot()) //not waiting to cool down, fire away!
    input.SetWeapon();
}


bool CSeekAndDestroy::IsTooHot() {
 float temp = mPilot.GetShip().GetWeapons().GetTemperature();
 if(!mWait && temp > 0.95) mWait = true; //too hot, wait
 if(mWait  && temp < 0.7)  mWait = false; //histeresis
 return mWait;
}
