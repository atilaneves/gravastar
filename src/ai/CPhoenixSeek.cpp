#include "CPhoenixSeek.hpp"
#include "CSeekFactory.hpp"
#include "CPilotBot.hpp"
#include "CPilots.hpp"
#include "CScramble.hpp"
#include "CPilotInputBot.hpp"
#include "CShip.hpp"
#include "CActionPicker.hpp"



REG_SEEK("Phoenix", CPhoenixSeek)



CPhoenixSeek::CPhoenixSeek(CPilotBot &pilot):
   CSeekAndDestroy(pilot) {

}


void CPhoenixSeek::SetShootControl(CPilotInputBot &input) {
  if(mPilot.GetShip().GetWeapons().CanSuper())
    input.SetSuper();
  else if(CActionPicker::IsNearlyDead(mPilot.GetShip()))
    input.SetSpecial();
  else if(!IsTooHot()) //not waiting to cool down, fire away!
    input.SetWeapon();
}
