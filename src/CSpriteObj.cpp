#include "CSpriteObj.hpp"
#include "CSpriteObjs.hpp"
#include "CGravSprite.hpp"
#include "CLevel.hpp"


CSpriteObj::CSpriteObj(CLevel &level, const CVector2 &pos):
  mLevel(level), mPos(pos), mUpdated(false) {

  CSpriteObjs::AddObj(this);
}


CSpriteObj::~CSpriteObj() {

}


void CSpriteObj::Draw() {
  GetSprite().Draw(mLevel.GetCanvas(), GetTopLeftX(), GetTopLeftY());
}


void CSpriteObj::Erase() {
  GetSprite().Erase(mLevel.GetCanvas(), GetTopLeftX(), GetTopLeftY());
}


bool CSpriteObj::InSprite(CScreenPos pos) { //is it in here?

 if(pos.GetX() >= GetTopLeftX() && pos.GetX() < GetTopLeftX() + GetWidth() && 
    pos.GetY() >= GetTopLeftY() && pos.GetY() < GetTopLeftY() + GetHeight() &&
    GetSprite().InSprite(pos.GetX() - GetTopLeftX(),
			 pos.GetY() - GetTopLeftY())) //bounding box
    return true;
 else
    return false;
}


void CSpriteObj::CheckCollision(float dt) {
  positions_t collisions = GetCollisions();
  if(!collisions.size()) return; //no collisions then
  for(unsigned int i = 0; i < collisions.size(); i++) {
    if(i > 0) break;
    CSpriteObj *hitObj = CSpriteObjs::HitObj(collisions[i]);
    if(hitObj) Hit(*hitObj, collisions[i], dt);
    else       HitTerrain(collisions[i], dt);
  }
}


positions_t CSpriteObj::GetCollisions() const {
  return GetSprite().Collided(mLevel.GetCanvas(), mPos);
}


bool CSpriteObj::Collided() const { 
  return GetCollisions().size() > 0;
}


bool CSpriteObj::Collided(const CSpriteObj& obj) const {
  return GetSprite().Collided(mLevel.GetCanvas(), obj.GetSprite(),
			      mPos, obj.GetPos());
}
