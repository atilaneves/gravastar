#include "CXbow.hpp"
#include "CShipFactory.hpp"
#include "CProjLauncher.hpp"
#include "CNose.hpp"
#include "CLevel.hpp"
#include "CDeflector.hpp"
#include "CSpriteObjs.hpp"
#include <math.h>

static std::string gShipName = "Xbow";
static std::string gFollowName = "deflector";
static std::string gShotName = "bolt";
static std::string gSuperName = "superBolt";

REG_FOLLOW_SHIP(gShipName, CXbow, gShotName, gFollowName,
                CDeflector, CFollowSpecial)
REG_WEAPON_PROJ(gShotName, CProjectile)
REG_EXTRA_BLUEPRINT(gShipName, gSuperName)

CXbow::CXbow(const CShipBluePrint &bluePrint, CPilot &pilot, CLevel &level)
    : CShip(bluePrint, pilot, level), mDeflector(nullptr) {}

void CXbow::UseWeapon(float dt) {
  if(mWeapons.IsSpecialActive()) return;
  CVector2 pos = CProjLauncher::GetLaunchPos(mWeapons.GetWeaponSprite(), dt,
                                             *this, 0.75);
  CVector2 vel = CProjLauncher::GetLaunchVel(*this, 700);
  mWeapons.UseWeaponAt(pos, vel, gShotName);
}



void CXbow::UseSpecial(float dt) {
    mDeflector = mWeapons.UseSpecialAt(mPos, mVel, gFollowName);
    //if a projectile hits both the deflector and the ship, the
    //deflector should have priority, so we change its order in the queue
    CSpriteObjs::RemoveObj(mDeflector); //take it off the back of the list
    bool back = false;
    CSpriteObjs::AddObj(mDeflector, back); //add it to the front
}


void CXbow::UseSuper(float dt, bool use) {
  CVector2 vel = CProjLauncher::GetLaunchVel(*this, 800);
  const CSpriteVector& sprites = mExtraProjBluePrint.GetSprites();
  CVector2 pos = CProjLauncher::GetLaunchPos(*sprites[0], dt, *this, 0.8);
  bool shadow = true;
  new CProjectile(mExtraProjBluePrint, *this, pos, vel, shadow);
}



bool CXbow::IsWithinCone(const CVector2& pos) const {
  const float theta = (pos - mPos).Theta();
  const float maxDiff = 0.35;
  return fabs(theta - mNose.GetAngle()) < maxDiff ||
    fabs(theta + 2*M_PI - mNose.GetAngle()) < maxDiff;
}


void CXbow::Hit(CProjectile& proj, CScreenPos pos, float dt) {
  if(mWeapons.IsSpecialActive() &&  IsWithinCone(proj.GetPos())) {
    if(!mDeflector->Collided(proj)) {
      if(proj.IsUpdated()) proj.Erase();
      proj.Move(-1.5*dt);
      if(proj.IsUpdated()) proj.Draw();
    }
    mDeflector->Hit(proj, CScreenPos(proj.GetPos()), dt);
  }
  else
    CShip::Hit(proj, pos, dt);
}
