#ifndef CWEAPONFOLLOW_H
#define CWEAPONFOLLOW_H


#include "CFollower.hpp"


class CWeaponFollow: public CFollower {

 public:

  CWeaponFollow(const CSpriteVector &sprites, CLevel &level, CMoverObj &mover,
		CSound *sound = 0, const CVector2& offset = CVector2(0, 0));

  virtual void Hit(CSpriteObj&   obj, CScreenPos pos, float dt);
  virtual void Hit(CProjectile& proj, CScreenPos pos, float dt);
  virtual void Hit(CShip&       ship, CScreenPos pos, float dt);
  virtual void HitTerrain(const CScreenPos &where, float dt);
  virtual void Move(float dt);

  void SetDamage(float amount) { mDamage = amount; }


 private:

  float mDamage;


};


#endif
