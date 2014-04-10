#ifndef CWEAPON_H
#define CWEAPON_H


class CPilotInput;
class CShip;
class CShipBluePrint;
class CProjBluePrint;
class CLevel;
class CGravSprite;
class CProjectile;
#include "CSound.hpp"
#include "CVector2.hpp"


class CWeapon {

public:

  CWeapon(const CShipBluePrint &bluePrint, CShip& ship, CLevel& level);

  void  ApplyInput(const CPilotInput& input);
  const CGravSprite& GetSprite() const;
  float GetTemperature() const { return mTemperature/mMaxTemperature; }
  void  Update(float dt);
  CProjectile* UseAt(const CVector2& pos, const CVector2& vel,
                     const std::string& name = "");


private:

  int mFastRate, mSlowRate;
  float mMaxTemperature, mCoolingRate;
  bool mFiring;
  float mTemperature;
  const CProjBluePrint& mBluePrint;
  CShip& mShip;
  CLevel& mLevel;
  CSound  mSound;

  int   GetRate() const;
  void  KeepTempInRange();


};


#endif
