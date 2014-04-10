#include "CArrow.hpp"
#include "CShipFactory.hpp"
#include "CHomingMissile.hpp"
#include "CProjLauncher.hpp"
#include "CNose.hpp"
#include "CGravityProj.hpp"
#include <math.h>


static std::string gMissName = "homingMissile";
static std::string gShotName = "plasma";
REG_PROJ_SHIP("Arrow", CArrow, gShotName, gMissName, CHomingMissile,
	      CProjSpecial)
REG_WEAPON_PROJ(gShotName, CProjectile)
REG_EXTRA_BLUEPRINT("Arrow", "fusion")


CArrow::CArrow(const CShipBluePrint& bluePrint, CPilot& pilot, CLevel &level):
    CShip(bluePrint, pilot, level) {

}


void CArrow::UseWeapon(float dt) {
  const double dist = 1, velNorm = 350;
  const float velAngle = CNose::NoseIndex2Angle(GetNose());
  CVector2 vel = CVector2(velAngle) * velNorm + mVel * 0.7;
  CVector2 pos = CProjLauncher::GetLaunchPos(mWeapons.GetWeaponSprite(), dt,
					     *this, dist);
  mWeapons.UseWeaponAt(pos, vel, gShotName);
}


void CArrow::UseSpecial(float dt) {
  const float dist = 0.8, velNorm = 325;
  const float velAngle = CNose::NoseIndex2Angle(GetNose());
  CVector2 vel = CVector2(velAngle) * velNorm;
  CVector2 pos = CProjLauncher::GetLaunchPos(mWeapons.GetSpecialSprite(), dt,
					     *this, dist);
  bool shadow = false;
  mWeapons.UseSpecialAt(pos, vel, gMissName, shadow);  
}


void CArrow::UseSuper(float dt, bool use) {
  const float dist = 0.85, velNorm = 500;
  const float velAngle = CNose::NoseIndex2Angle(GetNose());
  CVector2 vel = CVector2(velAngle) * velNorm;
  const CSpriteVector& sprites = mExtraProjBluePrint.GetSprites();
  CVector2 pos = CProjLauncher::GetLaunchPos(*sprites[0], dt, *this, dist);
  bool shadow = true;
  new CProjectile(mExtraProjBluePrint, *this, pos, vel, shadow);

}
