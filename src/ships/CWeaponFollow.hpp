#ifndef CWEAPONFOLLOW_H
#define CWEAPONFOLLOW_H


#include "CFollower.hpp"


class CWeaponFollow: public CFollower {

 public:
   CWeaponFollow(const CSpriteVector &sprites, CLevel &level, CMoverObj &mover,
                 CSound *sound = nullptr,
                 const CVector2 &offset = CVector2(0, 0));

  virtual void Hit(CSpriteObj &obj, CScreenPos pos, float dt) override;
  virtual void Hit(CProjectile &proj, CScreenPos pos, float dt) override;
  virtual void Hit(CShip &ship, CScreenPos pos, float dt) override;
  virtual void HitTerrain(const CScreenPos &where, float dt) override;
  virtual void Move(float dt) override;

  void SetDamage(float amount) { mDamage = amount; }


 private:

  float mDamage;


};


#endif
