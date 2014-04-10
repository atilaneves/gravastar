#include "CAbsorber.hpp"
#include "CProjectile.hpp"
#include "CShip.hpp"



CAbsorber::CAbsorber(const CSpriteVector &sprites, CLevel &level,
		     CMoverObj &obj, CSound *sound , const CVector2& offset):
  CFollower(sprites, level, obj, sound, offset) {

}


void CAbsorber::Hit(CSpriteObj& obj, CScreenPos pos, float dt) {
  CProjectile *proj = dynamic_cast<CProjectile*>(&obj);
  if(proj) Hit(*proj, pos, dt);
}


void CAbsorber::Hit(CProjectile& proj, CScreenPos pos, float dt) {
  mFollowed.Hit(proj, pos, dt);
}


void CAbsorber::Move(float dt) {
  CFollower::Move(dt);
  CheckCollision(dt);
}
