#include "CActionPicker.hpp"
#include "CPilotBot.hpp"
#include "CSeekFactory.hpp"
#include "CShip.hpp"
#include "CShips.hpp"
#include "CPilots.hpp"
#include "CPowerups.hpp"
#include "CInvulnerable.hpp"
#include "CEMB.hpp"


CPowerups* CActionPicker::sPowerups = 0;


CActionPicker::CActionPicker(CPilotBot &pilot):
  mPilot(pilot), mWasRecharging(false), mFlee(pilot), mWait(pilot),
  mSeekPowerup(pilot, *sPowerups) {

  const std::string& name = mPilot.GetShipName();
  mSeekAndDestroy.reset(CSeekFactory::Instance().CreateObject(name, mPilot));

  if(!mSeekAndDestroy.get()) //no specialised one for this ship
    mSeekAndDestroy.reset(new CSeekAndDestroy(mPilot)); //generic
}


CBotAction& CActionPicker::GetAction() {
  CBotAction &action = PickAction();
  action.Think();
  return action;
}


CBotAction& CActionPicker::PickAction() {
  CShip& ship = mPilot.GetShip();

  if(ship.IsEffectOn(CEMB::GetID())) return mFlee;

  if(CShips::IsAllElseInvulnerable(ship)) { 
    if(ship.IsEffectOn(CInvulnerable::GetID())) return *mSeekAndDestroy;
    else                                        return mFlee;
  }
  
  if(ship.GetWeapons().IsSuperActive()) return *mSeekAndDestroy;

  float dist = sPowerups->NearestDistance(ship.GetPos());
  if(dist < 40 || (dist < 200 && CPilots::IsCoastClear(mPilot)))
    return mSeekPowerup;

  if(CPilots::IsCoastClear(mPilot)) {
    if(mWasRecharging && IsGaugeBelow(ship, 1)) //not full yet
      return mFlee;
    else if(IsGaugeBelow(ship, 0.5)) {
      mWasRecharging = true;
      return mFlee;
    }
  }
  
  mWasRecharging = false; //if we got here, this is false

  if(!CPilots::IsAlone(mPilot)) //not alone, kill sb!
    return *mSeekAndDestroy;
  else //wait til sb spawns
    return mWait;
}


bool CActionPicker::IsNearlyDead(CShip &ship) {
  return ship.GetHull() / ship.GetMaxHull() < 0.25 &&
    ship.GetWeapons().GetSpecialGauge() /
    ship.GetWeapons().GetMaxSpecialGauge() < 0.2 &&
    !ship.GetWeapons().CanSuper();
}


bool CActionPicker::IsGaugeBelow(CShip &ship, float amount) {
 float hull    = ship.GetHull() / ship.GetMaxHull();
 float special = ship.GetWeapons().GetSpecialGauge() /
                 ship.GetWeapons().GetMaxSpecialGauge();
 return (hull    < amount && ship.GetAura().GetBaseHull()    > 0.001) ||
        (special < amount && ship.GetAura().GetBaseSpecial() > 0.001);
}
