#include "CMenuIconSprite.hpp"
#include "CSprite.hpp"
#include "CCanvas.hpp"



CMenuIconSprite::CMenuIconSprite(CSprite &sprite):
   mSprite(sprite) {

}


void CMenuIconSprite::Draw(CCanvas &canvas, int x, int y, bool highlight) const {
  x += 20  - mSprite.GetWidth()/2;
  y += mSprite.GetHeight()/2;
  mSprite.Draw(canvas,x,y);
}


int CMenuIconSprite::GetHeight() const {
  return mSprite.GetHeight();
}


int CMenuIconSprite::GetWidth() const {
  return mSprite.GetWidth();
}
