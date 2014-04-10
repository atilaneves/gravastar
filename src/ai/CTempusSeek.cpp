#include "CTempusSeek.hpp"
#include "CSeekFactory.hpp"
#include "CPilotBot.hpp"
#include "CPilots.hpp"
#include "CPilotInputBot.hpp"
#include "CShip.hpp"
#include "CTempus.hpp"


REG_SEEK("Tempus", CTempusSeek)


CTempusSeek::CTempusSeek(CPilotBot &pilot):
   CSeekAndDestroy(pilot), mDetonate(false) {

}


void CTempusSeek::Think() {
  CSeekAndDestroy::Think();
  mDetonate = false;
  if(mTargetIndex != -1) { //we have a target
    const CShip &ship = CPilots::GetPilot(mTargetIndex).GetShip();
    CTempus *tempus = (CTempus*)&mPilot.GetShip();
    
    if(tempus->IsSpecialActive() &&
       (ship.GetPos() - tempus->GetSpecialPos()).Radius() < 200)
      mDetonate = true; //cluster!
  }
}


void CTempusSeek::SetShootControl(CPilotInputBot &input) {

  if(mPilot.GetShip().GetWeapons().CanSuper())
    input.SetSuper();
  else if(mPilot.GetShip().GetWeapons().CanSpecial() &&
	  !CPilots::GetPilot(mTargetIndex).GetShip().IsStopped())
    input.SetSpecial();
  else if(mDetonate)
    input.SetSpecial();
  else if(!IsTooHot()) //not waiting to cool down, fire away!
    input.SetWeapon();
}
