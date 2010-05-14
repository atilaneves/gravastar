#include "CSeekPowerup.hpp"
#include "CPilotBot.hpp"
#include "CAstar.hpp"
#include "CPoint2D.hpp"
#include "CBase.hpp"
#include "CShips.hpp"
#include "CPowerups.hpp"
#include "CPowerup.hpp"
#include <math.h>
#include <assert.h>


CSeekPowerup::CSeekPowerup(CPilotBot &pilot, const CPowerups &powerups):
   CBotAction(pilot), mPowerups(powerups) {

}


void CSeekPowerup::Think() {
  mTargetIndex = -1;
  mTargetAngle = M_PI_2;
  mNoseAngle   = mTargetAngle;
  CShip& ship  = mPilot.GetShip();
  const CPowerup* powerup = mPowerups.NearestPowerup(ship.GetPos());
  assert(powerup);
  
  if(!mPilot.IsClearLine(powerup->GetPos()) || 
     (ship.GetPos() - powerup->GetPos()).Radius() > 50) {
    CPoint2D::SetStepSizes(ship, 20, 60);
    CAstar<CPoint2D> search(new CPoint2D(ship.GetPos()),
			    new CPoint2D(powerup->GetPos()));
    int op = search.Search();
    
    if(op >= 0) {
      mTargetAngle = CPoint2D::OpToAngle(op);
      SetNoseAngle();
    }
  }
  else {
    mTargetAngle = (powerup->GetPos() - ship.GetPos()).Theta();
    mNoseAngle   = mTargetAngle;
  }

  if(mTargetAngle < 0) mTargetAngle += 2*M_PI; //guarantee [0,2pi[ interval
  if(mNoseAngle   < 0) mNoseAngle   += 2*M_PI; //guarantee [0,2pi[ interval
}
