#include "CLightning.hpp"
#include "CProjectile.hpp"
#include "CShip.hpp"



CLightning::CLightning(const CSpriteVector &sprites, CLevel &level,
		       CMoverObj &obj, CSound *sound , const CVector2& offset):
  CWeaponFollow(sprites, level, obj, sound, offset) {

  SetDamage(30);
}



void CLightning::Move(float dt) {
  CWeaponFollow::Move(dt);
  float magic = 62;
  CShip *myShip = (CShip*)&mFollowed;
  float vx = mFollowed.GetVel().GetX();
  int nose = myShip->GetNose();

  if(nose <= CNose::kNbNoses/4 || nose>=(3*CNose::kNbNoses)/4) {//right
    magic *= 0.88;
    if(vx > 0) magic += vx*0.01;
  }
  else { //left
    magic *= 0.85;
    if(vx < 0) magic += -vx*0.01;
  }

  mPos += CVector2(CNose::NoseIndex2Angle(nose)) * magic;
  CheckCollision(dt);
}
