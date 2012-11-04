#ifndef CWEAPONS_H
#define CWEAPONS_H


class CPilotInput;
class CShip;
class CLevel;
class CShipBluePrint;
#include "CVector2.hpp"
#include "CWeapon.hpp"
#include "CSpecial.hpp"
#include "CSuper.hpp"
#include <string>
#include <memory>


class CWeapons {

public:

  CWeapons(const std::string& name, const CShipBluePrint& bluePrint,
           CShip &ship, CLevel &level);
  
  const CGravSprite& GetSpecialSprite() const {
    return mSpecial->GetSprite();
  }

  const CGravSprite& GetWeaponSprite() const {
    return mWeapon->GetSprite();
  }

  void  AddSpecialGauge(float amount) { mSpecial->LoseGauge(-amount); }
  void  AddSuperGauge(float amount)   { mSuper.AddGauge(amount); }
  void  ApplyInput(const CPilotInput& input);
  bool  CanSpecial() const { return mSpecial->CanUse(); }
  bool  CanSuper() const { return mSuper.CanUse(); }
  void  DrawStats(CCanvas &canvas) const;
  float GetDepletion() const { return mSpecial->GetDepletion(); }
  float GetMaxSpecialGauge() const { return mSpecial->GetMaxGauge(); }
  float GetSpecialGauge() const { return mSpecial->GetGauge(); }
  float GetSuperGauge()   const { return mSuper.GetGauge(); }
  float GetTemperature() const { return mWeapon->GetTemperature(); }
  bool  IsAtMax()     const     { return mSpecial->IsAtMax();     }
  bool  IsSpecialActive()  { return mSpecial->IsActive(); }
  bool  IsSuperActive()  { return mSuper.IsActive(); }
  void  LoseGauge(float amount) { mSpecial->LoseGauge(amount);    }
  void  SetSuperGauge(float amount)   { mSuper.SetGauge(amount); }
  void  Update(float dt);
  CMoverObj* UseSpecialAt(const CVector2& pos, const CVector2& vel,
                          const std::string& name, bool shadow = false) {
          return mSpecial->UseAt(pos, vel, name, shadow); }
  CProjectile* UseWeaponAt(const CVector2& pos, const CVector2& vel,
                           const std::string& name = "") {
          return mWeapon->UseAt(pos, vel, name); }


private:

  std::unique_ptr<CWeapon>  mWeapon;
  std::unique_ptr<CSpecial> mSpecial;
  CSuper mSuper;

};


#endif
