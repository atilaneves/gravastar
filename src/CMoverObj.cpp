#include "CMoverObj.hpp"
#include "CVector2.hpp"
#include "CCanvas.hpp"
#include "CLevel.hpp"
#include <cmath>



CMoverObj::CMoverObj(const CSpriteVector &sprites, CLevel &level,
		     const CVector2 &pos, const CVector2 &vel):
  CSpriteObj(level, pos),
  mSprites(sprites),
  mVel(vel) {

}


void CMoverObj::Update(float dt) {
  Move(dt);
  KeepInBounds();
}


void CMoverObj::Move(float dt) {
  if(IsStopped()) return;
  mVel += CalcAcc() * dt;
  mPos += mVel      * dt;
}


void CMoverObj::KeepInBounds() {

  const CCanvas &canvas = mLevel.GetCanvas();

  if(mPos.GetX() < GetWidth() / 2)
    OutOfBounds(0);
  if(mPos.GetX() > canvas.GetWidth() - GetWidth() / 2) //thu the right
    OutOfBounds(M_PI);
  if(mPos.GetY() < GetHeight() / 2) //through the top of the level
    OutOfBounds(0.5*M_PI);
  if(mPos.GetY() > canvas.GetHeight() - GetHeight() / 2) //thu the bottom
    OutOfBounds(1.5*M_PI);
}
