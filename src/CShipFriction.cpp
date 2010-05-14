#include "CShipFriction.hpp"
#include "CShip.hpp"
#include "CLevel.hpp"


CShipFriction::CShipFriction(const CShip &ship, const CLevel &level):
  mInTerrain(false), mShip(ship), mLevel(level){

}


CVector2 CShipFriction::CalcAcc() {
 return (-GetFriction()*mShip.GetVel());
}


float CShipFriction::GetFriction() {
  float f = mInTerrain ? mLevel.GetLandFriction() : mLevel.GetAirFriction();
  mInTerrain = false;
  return f;
}
