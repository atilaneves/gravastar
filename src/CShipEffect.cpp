#include "CShipEffect.hpp"
#include "CSpriteObj.hpp"
#include "CShip.hpp"
#include "CShips.hpp"



CShipEffect::CShipEffect(CLevel &level, CShip& ship, float duration):
  mLevel(level), mShip(ship), mDuration(duration) {

}


void CShipEffect::Start(float duration) {
  if(duration < 0) //standard case, use defined duration
    mCounter.Start(mDuration);
  else //override and use the duration sent to us
    mCounter.Start(duration);
  AtStart();
}


void CShipEffect::Reset() {
  mCounter.Reset();
}


void CShipEffect::Update() {
  if(!CShips::HasShip(&mShip) || //ship inactive (dead + past pause)
     (!WorksOnDeadShip() && !mShip.IsAlive())) { //ship dead
    mCounter.Reset();
    AtJustFinished();
  }
  if(mCounter.IsActive())
    Affect(); //do our thing to the ship
  else if(JustFinished())
    AtJustFinished(); //no longer on
}
