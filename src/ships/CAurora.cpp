#include "CAurora.hpp"
#include "CShipFactory.hpp"
#include "CProjLauncher.hpp"
#include "CNose.hpp"
#include "CGravityProj.hpp"
#include <math.h>


static std::string gMissName = "shard";
static std::string gShotName = "shard";
REG_PROJ_SHIP("Aurora", CAurora, gShotName, gMissName, CProjectile,
              CProjSpecial)
REG_WEAPON_PROJ(gShotName, CGravityProj)


CAurora::CAurora(const CShipBluePrint& bluePrint, CPilot& pilot,
                 CLevel &level):
    CShip(bluePrint, pilot, level) {

}


void CAurora::UseWeapon(float dt) {
  SpawnShard(dt, 0);
}



void CAurora::UseSpecial(float dt) {
  mVel = CVector2(mNose.GetAngle()) * 550;
}


void CAurora::UseSuper(float dt, bool use) {
  const float theta  = M_PI / 4;
  const float dAngle = (rand()/float(RAND_MAX)) *  2*theta - theta;
  const bool shadow  = true;
  SpawnShard(dt, dAngle, shadow);
}



void CAurora::SpawnShard(float dt, float dAngle, bool shadow) {
  const float dist = 0.75, velNorm = 500;
  CVector2 vel = CProjLauncher::GetLaunchVel(*this, velNorm, dAngle);
  CVector2 pos = CProjLauncher::GetLaunchPos(mWeapons.GetSpecialSprite(), dt,
                                             *this, dist, dAngle);
  mWeapons.UseSpecialAt(pos, vel, gShotName, shadow);
}



void CAurora::LoseHull(float amount, CPilot &pilot) {
  if(&pilot != &mPilot) CShip::LoseHull(amount, pilot);
}
