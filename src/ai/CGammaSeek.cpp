#include "CGammaSeek.hpp"
#include "CSeekFactory.hpp"
#include "CPilotBot.hpp"
#include "CPilots.hpp"
#include "CScramble.hpp"
#include "CPilotInputBot.hpp"
#include "CShip.hpp"
#include "CGamma.hpp"


REG_SEEK("Gamma", CGammaSeek)



CGammaSeek::CGammaSeek(CPilotBot &pilot):
   CSeekAndDestroy(pilot) {

}


void CGammaSeek::SetShootControl(CPilotInputBot &input) {

  CGamma *gamma = dynamic_cast<CGamma*>(&mPilot.GetShip());

  if(mPilot.GetShip().GetWeapons().CanSuper())
    input.SetSuper();
  else if(mPilot.GetShip().GetWeapons().CanSpecial() &&
	  gamma && !gamma->IsSpecialActive())
    input.SetSpecial();
  else if(!IsTooHot()) //not waiting to cool down, fire away!
    input.SetWeapon();
  

}
