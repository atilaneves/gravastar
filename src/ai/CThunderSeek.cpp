#include "CThunderSeek.hpp"
#include "CSeekFactory.hpp"
#include "CPilotBot.hpp"
#include "CPilots.hpp"
#include "CScramble.hpp"
#include "CPilotInputBot.hpp"
#include "CShip.hpp"



REG_SEEK("Thunderblade", CThunderSeek)
REG_SEEK2("Aurora", CThunderSeek)
REG_SEEK3("Soliton", CThunderSeek)


CThunderSeek::CThunderSeek(CPilotBot &pilot):
   CSeekAndDestroy(pilot) {

}


void CThunderSeek::SetShootControl(CPilotInputBot &input) {

  CVector2 dist = CPilots::GetPilot(mTargetIndex).GetShip().GetPos() -
    mPilot.GetShip().GetPos();
  double maxDistSpecial = 60 + mPilot.GetShip().GetHeight();
  double maxDistSuper   = 90 + mPilot.GetShip().GetHeight();

  if(mPilot.GetShip().GetWeapons().CanSuper() &&
     dist.Radius() < maxDistSuper)
    input.SetSuper();
  else if(mPilot.GetShip().GetWeapons().GetSpecialGauge() > 0.1 &&
          dist.Radius() < maxDistSpecial)
    input.SetSpecial();
  else //not waiting to cool down, fire away!
    input.SetWeapon();
}
