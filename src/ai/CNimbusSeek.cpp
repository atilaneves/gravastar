#include "CNimbusSeek.hpp"
#include "CSeekFactory.hpp"
#include "CPilotBot.hpp"
#include "CPilots.hpp"
#include "CScramble.hpp"
#include "CPilotInputBot.hpp"
#include "CNimbus.hpp"
#include "CShip.hpp"



REG_SEEK("Nimbus", CNimbusSeek)


CNimbusSeek::CNimbusSeek(CPilotBot &pilot):
   CSeekAndDestroy(pilot),
   mNoClearLine(false) {

}


bool CNimbusSeek::WantsToShoot() {
  CVector2 shipPos = CPilots::GetPilot(mTargetIndex).GetShip().GetPos();
  mNoClearLine = !mPilot.IsClearLine(shipPos);
  return mNoClearLine;
}


void CNimbusSeek::SetShootControl(CPilotInputBot &input) {

  if(mTargetIndex == -1)
    input.SetSpecial();
  else if(mNoClearLine) {
    if(mPilot.GetShip().GetWeapons().CanSuper())
      input.SetSuper();
    else
      input.SetSpecial();
  }
  else if(!IsTooHot()) //not waiting to cool down, fire away!
    input.SetWeapon();
}
