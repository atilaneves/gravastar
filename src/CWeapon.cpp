#include "CWeapon.hpp"
#include "CShip.hpp"
#include "CPilot.hpp"
#include "CShipBluePrint.hpp"
#include "CWeaponTimer.hpp"
#include "CProjectile.hpp"
#include "CCoolant.hpp"
#include "CProjectileFactory.hpp"
#include "CEMB.hpp"


CWeapon::CWeapon(const CShipBluePrint &shipBluePrint, CShip &ship,
		 CLevel& level):
  mFastRate(shipBluePrint.mFastRate), mSlowRate(shipBluePrint.mSlowRate),
  mMaxTemperature(shipBluePrint.mMaxTemperature),
  mCoolingRate(shipBluePrint.mCoolingRate),
  mFiring(false), mTemperature(0),
  mBluePrint(*shipBluePrint.mWeaponBluePrint),
  mShip(ship), mLevel(level), mSound(mBluePrint.mSound) {


}


void CWeapon::ApplyInput(const CPilotInput& input) {
  if(input.Weapon() && !mShip.IsEffectOn(CEMB::GetID())) mFiring = true;
}


void CWeapon::Update(float dt) {

  if(mFiring &&
     CWeaponTimer::Instance().IsReady(mShip.GetPilot().GetIndex(),
				      GetRate())) {
    if(!mShip.IsEffectOn(CCoolant::GetID()))
      mTemperature += 1.0/CWeaponTimer::Instance().GetFrequency(); //heats up
    mShip.UseWeapon(dt);
    mFiring = false;
  }
  if(!mFiring)
    mTemperature -= mCoolingRate/CWeaponTimer::Instance().GetFrequency();

  KeepTempInRange();
  mFiring = false;
}


void CWeapon::KeepTempInRange() {
 if(mTemperature < 0)                mTemperature = 0;
 if(mTemperature >= mMaxTemperature) mTemperature = mMaxTemperature;
}


int CWeapon::GetRate() const {
 if(GetTemperature() < 0.9) //90%
    return mFastRate;
 else
    return mSlowRate;
}


CProjectile* CWeapon::UseAt(const CVector2& pos, const CVector2& vel,
			    const std::string& name) {
  mSound.Play(pos);
  bool shadow = false;
  CProjectile *proj =
    CProjectileFactory::Instance().CreateObject(name, mBluePrint, mShip,
						pos, vel, shadow);
  if(!proj) //no specific projectile, do a generic one
    proj = new CProjectile(mBluePrint, mShip, pos, vel, shadow);

  return proj;
}


const CGravSprite& CWeapon::GetSprite() const {
  return *((mBluePrint.GetSprites())[0]);
}
