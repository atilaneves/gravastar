#include "CVoidhar.hpp"
#include "CShipFactory.hpp"
#include "CProjLauncher.hpp"
#include "CSpriteObjs.hpp"
#include "CShips.hpp"
#include "CEMP.hpp"
#include "CEMB.hpp"
#include "CShipBluePrint.hpp"
#include "CShipSounds.hpp"
#include "CSpecialExplosion.hpp"
#include <math.h>


static std::string gShipName = "Voidhar";
static std::string gMissName = "wave";
static std::string gShotName = "wave";


REG_PROJ_SHIP(gShipName, CVoidhar, gShotName, gMissName,
              CProjectile, CProjSpecial)
REG_WEAPON_PROJ(gShotName, CProjectile)



CVoidhar::CVoidhar(const CShipBluePrint& bluePrint,
                   CPilot& pilot, CLevel &level):
  CShip(bluePrint, pilot, level),
  mEMP(bluePrint.mSounds.mEMP),
  mSpecialExpSprites(bluePrint.mSpecialExpSprites) {

}


void CVoidhar::UseWeapon(float dt) {
  CVector2 pos = CProjLauncher::GetLaunchPos(mWeapons.GetWeaponSprite(), dt,
                                             *this, 0.75);
  CVector2 vel = CProjLauncher::GetLaunchVel(*this, 400);
  mWeapons.UseWeaponAt(pos, vel, gShotName);
}



void CVoidhar::UseSpecial(float dt) {
  float duration = 6;
  CShips::StartEffect(this, CEMP::GetID(), duration);
  new CSpecialExplosion(mLevel, mPos, mSpecialExpSprites, mEMP, *this);
}


void CVoidhar::UseSuper(float dt, bool use) {
  float duration = 15;
  CShips::StartEffect(this, CEMB::GetID(), duration);
  new CSpecialExplosion(mLevel, mPos, mSpecialExpSprites, mEMP, *this);
  mEMP.Play(mPos);
  mEMP.Play(mPos);
  mEMP.Play(mPos);
}
