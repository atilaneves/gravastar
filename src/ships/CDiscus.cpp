#include "CDiscus.hpp"
#include "CShipFactory.hpp"
#include "CProjLauncher.hpp"
#include "CNose.hpp"
#include "CLevel.hpp"
#include "CAbsorber.hpp"
#include <algorithm>
#include <math.h>



static std::string gFollowName = "absorber";
static std::string gShotName = "miniBullet";
REG_FOLLOW_SHIP("Discus", CDiscus, gShotName, gFollowName,
                CAbsorber, CFollowSpecial)


CDiscus::CDiscus(const CShipBluePrint& bluePrint,
		 CPilot& pilot, CLevel &level):
    CShip(bluePrint, pilot, level) {


}


void CDiscus::UseWeapon(float dt) {
  float dPosAngle = M_PI/16; //small variation in angle
  float dVelAngle = M_PI/20;
  SpawnBullet(dt, -dPosAngle, -dVelAngle);
  SpawnBullet(dt, dPosAngle, dVelAngle);
}


void CDiscus::SpawnBullet(float dt, float dAngle, float dVelAngle) {

  const float dist = 0.5;
  const float velMin = 300;
  const float velNorm = std::max(velMin, mVel.Radius()) + mVel.Radius()/5;
  CVector2 vel = CProjLauncher::GetLaunchVel(*this, velNorm, dVelAngle);
  CVector2 pos = CProjLauncher::GetLaunchPos(mWeapons.GetSpecialSprite(), dt,
					     *this, dist, dAngle);
  mWeapons.UseWeaponAt(pos, vel, gShotName);
}



void CDiscus::UseSpecial(float dt) {
  mWeapons.UseSpecialAt(mPos, mVel, gFollowName);  
}


void CDiscus::UseSuper(float dt, bool use) {
  //dt isn't used cos this is called a certain number of times per second
  CExplosive::LoseHull(-1.2);
  mWeapons.AddSpecialGauge(0.33);
}


void CDiscus::LoseHull(float amount, CPilot &pilot) {
  if(mWeapons.IsSpecialActive() && &pilot != &mPilot) {
    CExplosive::LoseHull(-amount / 2);  //add hull
    mWeapons.AddSuperGauge(amount / 3); 
  }
 else
    CShip::LoseHull(amount, pilot);
}


CVector2 CDiscus::CalcAcc() {

  CVector2 acc = CShip::CalcAcc();

  if(!mEngine.IsOn() || mWeapons.IsSpecialActive()) {
    const float kDamp   = 15;
    const float kMaxVel = 37.5;
    if(mVel.Radius() > kMaxVel) acc += -kDamp * mVel;
  }

  return acc;
}
