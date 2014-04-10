#include "CLuna.hpp"
#include "CShipFactory.hpp"
#include "CProjLauncher.hpp"
#include "CNose.hpp"
#include "CBoomerang.hpp"
#include "CGravityProj.hpp"
#include <math.h>


static std::string gProjName = "boomerang";
static std::string gShotName = "shot";
REG_PROJ_SHIP("Luna", CLuna, gShotName, gProjName, CBoomerang, CProjSpecial)
REG_WEAPON_PROJ(gShotName, CGravityProj)



CLuna::CLuna(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level):
    CShip(bluePrint, pilot, level) {


}


void CLuna::UseWeapon(float dt) {
  const float shotVel = 300;
  for(int i=0; i<3; i++) SpawnShot(dt, i, shotVel);
}


void CLuna::SpawnShot(float dt, int shotIndex, float shotVel) {
  const int   kNbPos = 3; //# of cannons on the ship
  float dAngle = shotIndex % kNbPos == 0 ? 0 : 1.2;
  if(shotIndex % kNbPos == 1) dAngle *= -1; //left
  const float dist = fabs(dAngle) > 0.001 ? 0.6 : 0.15;
  float dDirAngle = shotIndex % kNbPos == 0 ? 0 : 1.5;
  if(shotIndex % kNbPos == 1) dDirAngle *= -1; //left
  double dDirAngle2 = 0;
  if(shotIndex >= kNbPos) { //super
    if(shotIndex/kNbPos==1) dDirAngle2 = -0.1; //shots 3,4,5
    else dDirAngle2 = 0.1; //shots 6,7,8
 }
  const float velAngle = CNose::NoseIndex2Angle(GetNose()) + dAngle -
                         dDirAngle - dDirAngle2;
  CVector2 vel = CVector2(velAngle) * shotVel + mVel;
  CVector2 pos = CProjLauncher::GetLaunchPos(mWeapons.GetSpecialSprite(), dt,
					     *this, dist, dAngle);
  mWeapons.UseWeaponAt(pos, vel, gShotName);
}



void CLuna::UseSpecial(float dt) {
  const float dist = 0.65, velNorm = 500;
  CVector2 vel = CProjLauncher::GetLaunchVel(*this, velNorm);
  CVector2 pos = CProjLauncher::GetLaunchPos(mWeapons.GetSpecialSprite(), dt,
					     *this, dist);
  bool shadow = false;
  mWeapons.UseSpecialAt(pos, vel, gProjName, shadow);  
}


void CLuna::UseSuper(float dt, bool use) {
  const float shotVel = 500;
  for(int i=0; i<9; i++) SpawnShot(dt, i, shotVel);
}
