#include "CPhoenix.hpp"
#include "CShipFactory.hpp"
#include "CHomingMissile.hpp"
#include "CProjLauncher.hpp"
#include "CNose.hpp"
#include "CGravityProj.hpp"
#include "CLevel.hpp"
#include "CNose.hpp"
#include "CInvulnerable.hpp"
#include <math.h>


static std::string gMissName = "homingMissile";
static std::string gShotName = "lavaBig";
REG_PROJ_SHIP("Phoenix", CPhoenix, gShotName, gMissName, CHomingMissile,
	      CProjSpecial)
REG_WEAPON_PROJ(gShotName, CProjectile)
REG_EXTRA_BLUEPRINT("Phoenix", "fusion")


CPhoenix::CPhoenix(const CShipBluePrint& bluePrint, CPilot& pilot,
		   CLevel &level):
    CShip(bluePrint, pilot, level) {

}


void CPhoenix::UseWeapon(float dt) {
  const double dist = 0.8, velNorm = 450;
  const float velAngle = CNose::NoseIndex2Angle(GetNose());
  CVector2 vel = CVector2(velAngle) * velNorm + mVel / 2;
  CVector2 pos = CProjLauncher::GetLaunchPos(mWeapons.GetWeaponSprite(), dt,
					     *this, dist);
  mWeapons.UseWeaponAt(pos, vel, gShotName);
}


void CPhoenix::UseSpecial(float dt) {
  mSpawn.Play(mPos);
  mPos = mLevel.GetFreePos(GetSprite()); //teleport!
  mVel = CVector2(0, 0);
  float orientation = CNose::kNbNoses / 4;
  float omega = 0;
  mNose.Set(orientation, omega);
}


void CPhoenix::UseSuper(float dt, bool use) {
  float duration = 8;
  StartEffect(CInvulnerable::GetID(), duration);
}
