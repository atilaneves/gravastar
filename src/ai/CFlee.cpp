#include "CFlee.hpp"
#include "CPilotBot.hpp"
#include "CAstar.hpp"
#include "CPoint2D.hpp"
#include "CBase.hpp"
#include "CShips.hpp"
#include "CLevel.hpp"
#include <math.h>


CFlee::CFlee(CPilotBot &pilot):
   CBotAction(pilot) {

}


void CFlee::Think() {

  SetDefaults();

  const CLevel &level = mPilot.GetShip().GetLevel();
  const CBase &base = *(level.GetBases()[GetBaseIndex()]);

  if(IsJustAboveBase(base)) return; //no need to look

  CPoint2D::SetStepSizes(mPilot.GetShip(), 20, 60);
  CAstar<CPoint2D> search(new CPoint2D(mPilot.GetShip().GetPos()),
			  new CPoint2D(base.GetPos()));
  int op = search.Search();
  
  if(op >= 0) {
    mTargetAngle = CPoint2D::OpToAngle(op);
    SetNoseAngle();
  }  
}


bool CFlee::IsJustAboveBase(const CBase& base) const {
  int bx = int(base.GetPos().GetX());
  int by = int(base.GetPos().GetY()) - base.GetHeight()/4; //top of base
  CShip& ship = mPilot.GetShip();
  int sx = int(ship.GetPos().GetX());
  int sy = int(ship.GetPos().GetY()) + ship.GetHeight()/4; //bottom of ship
  int maxDist = 40 + int(ship.GetVel().GetY() / 4) + ship.GetHeight();
  if(sy < by && by-sy < maxDist && abs(sx-bx) < base.GetWidth()/4) return true;
  return false;
}


void CFlee::SetDefaults() {
  //default values - used if ship's over the base
  mTargetIndex = -1;
  mTargetAngle = M_PI_2;
  mNoseAngle = 1.5 * M_PI;

  const float minVelX = 7.5*1000;
  const float minVelY = 55;
  CShip& ship = mPilot.GetShip();

  if(ship.GetVel().GetY() > minVelY ||
     fabs(mPilot.GetShip().GetVel().GetX()) > minVelX) 
    mTargetAngle = 1.5*M_PI; //thrust a bit to not bounce

  if(fabs(ship.GetVel().GetX()) > minVelX) //too fast in x
    mTargetAngle = mNoseAngle = ship.GetVel().GetX() > 0 ?
      M_PI + 0.1 : 2*M_PI - 0.1;
  else {//not too fast in x, just thrust slightly upwards
    mNoseAngle = 1.5*M_PI - ship.GetVel().GetX() * 0.05;
    if(ship.GetVel().GetY() > 100) mTargetAngle = 1.5*M_PI;
  }
}  


int CFlee::GetBaseIndex() const {

  const Bases_t& bases = mPilot.GetShip().GetLevel().GetBases();
  int baseIndex = 0;
  float minDist2 = 9e20;
 
  for(unsigned int b = 0; b < bases.size(); b++) {
    int bx = int(bases[b]->GetPos().GetX());
    int by = int(bases[b]->GetPos().GetY() -
		 bases[b]->GetHeight() / 2 - 1); //top of the base
    if(!CShips::IsClearLine(mPilot.GetShip(), bx, by)) { //nb else has
      CVector2 dist = CVector2(bx, by) - mPilot.GetShip().GetPos();
      if(dist.Radius2() < minDist2) {
	minDist2 = dist.Radius2();
	baseIndex = b;
      }
    }
  }
  
 return baseIndex;
}
