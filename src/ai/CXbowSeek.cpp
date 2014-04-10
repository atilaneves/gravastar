#include "CXbowSeek.hpp"
#include "CSeekFactory.hpp"
#include "CPilotBot.hpp"
#include "CPilots.hpp"
#include "CScramble.hpp"
#include "CPilotInputBot.hpp"
#include "CXbow.hpp"
#include <assert.h>


//REG_SEEK("Xbow", CXbowSeek)



CXbowSeek::CXbowSeek(CPilotBot &pilot):
   CSeekAndDestroy(pilot) {

}


void CXbowSeek::SetShootControl(CPilotInputBot &input) {

  CXbow    *xbow    = dynamic_cast<CXbow*>(&mPilot.GetShip());
  assert(xbow);
  bool okSpecial = xbow ? xbow->CanSpecial() : false;

  if(mPilot.GetShip().GetWeapons().CanSuper())
    input.SetSuper();
  else if(okSpecial && mPilot.GetShip().GetWeapons().CanSpecial())
    input.SetSpecial();
  else if(!IsTooHot()) //not waiting to cool down, fire away!
    input.SetWeapon();
}
