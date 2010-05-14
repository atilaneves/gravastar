#include "CDiscusSeek.hpp"
#include "CSeekFactory.hpp"
#include "CPilotBot.hpp"
#include "CPilotInputBot.hpp"
#include "CProjectiles.hpp"
#include "CShip.hpp"
#include "CInvulnerable.hpp"
#include "CPhantom.hpp"
#include "CXbow.hpp"
#include <assert.h>


REG_SEEK("Discus", CDiscusSeek)
REG_SEEK2("Phantom", CDiscusSeek)
REG_SEEK3("Phantom", CDiscusSeek)


CDiscusSeek::CDiscusSeek(CPilotBot &pilot):
  CSeekAndDestroy(pilot) {

}


void CDiscusSeek::Think() {
  CSeekAndDestroy::Think();
  if(CProjectiles::HasTowards(mPilot.GetShip()) &&
     !mPilot.GetShip().IsEffectOn(CInvulnerable::GetID()))
    mShieldCounter.Start(0.5); //use shield!
}


void CDiscusSeek::SetShootControl(CPilotInputBot &input) {

  if(mPilot.GetShip().GetWeapons().CanSuper())
    input.SetSuper();
  else if(WantsToShoot() && mPilot.GetShip().GetWeapons().CanSpecial()) {
    input.SetSpecial();
  }
  else if(!IsTooHot()) //not waiting to cool down, fire away!
    input.SetWeapon();
}
