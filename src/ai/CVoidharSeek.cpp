#include "CVoidharSeek.hpp"
#include "CSeekFactory.hpp"
#include "CPilotBot.hpp"
#include "CPilots.hpp"
#include "CEMP.hpp"
#include "CEMB.hpp"
#include "CPilotInputBot.hpp"
#include "CShip.hpp"



REG_SEEK("Voidhar", CVoidharSeek)



CVoidharSeek::CVoidharSeek(CPilotBot &pilot):
   CSeekAndDestroy(pilot) {

}


void CVoidharSeek::SetShootControl(CPilotInputBot &input) {

  if(mPilot.GetShip().GetWeapons().CanSuper())
    input.SetSuper();
  else if(mPilot.GetShip().GetWeapons().CanSpecial() &&
	  !CPilots::GetPilot(mTargetIndex).GetShip().
	  IsEffectOn(CEMP::GetID()) &&
	  !CPilots::GetPilot(mTargetIndex).GetShip().
	  IsEffectOn(CEMB::GetID()))
    input.SetSpecial();
  else if(!IsTooHot()) //not waiting to cool down, fire away!
    input.SetWeapon();
  

}
