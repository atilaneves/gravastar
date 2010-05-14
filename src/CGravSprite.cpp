#include "CGravSprite.hpp"
#include "CSpriteCanvas.hpp"
#include "CColour.hpp"


CGravSprite::CGravSprite(void *data, const CTeam &team,
			 float angle, float scale, int colour):
  mCollision((BITMAP*)data) {

  BITMAP *bmp = CSprite::CreateBitmap(data, angle, scale);
  CSpriteCanvas draw(bmp);
  CSpriteCanvas erase(bmp);

  Transform(bmp, team, colour, draw, erase);
  
  mSprite.reset(new CSprite(draw.GetData()));
  mErase.reset(new CSprite(erase.GetData()));
}


void CGravSprite::Transform(BITMAP *bmp, const CTeam &team, int colour,
			    CSpriteCanvas &draw, CSpriteCanvas &erase) {

  bool transform = team != CTeam::sWhite || colour >=0;
  transform = true;

  for(int x = 0; x < bmp->w; ++x) {     //loop through the bitmap
    for(int y = 0; y < bmp->h; ++y) {
      
      int col = getpixel(bmp, x, y);
      
      if(col != draw.GetMask()) { //non-transparent pixel: gotta draw
	if(transform) {
	  col = colour < 0 ? team.TransformColour(col) : colour;
	  draw.PutPixel(x, y, col); //draw (blue -> team)
	}
	erase.PutPixel(x, y, CColour::GetBlack()); //construct the erase bitmap
	mCollision.push_back(CSpriteCollision::SSpritePixel(x,y));
      }
    }
  }
}

void CGravSprite::Draw(CCanvas &canvas, int x, int y) const {
  mSprite->Draw(canvas, x, y);
}


void CGravSprite::Erase(CCanvas &canvas, int x, int y) const {
  mErase->Draw(canvas, x, y);
}


int CGravSprite::GetHeight() const {
  return mSprite->GetHeight();
}


int CGravSprite::GetWidth() const {
  return mSprite->GetWidth();
}


positions_t CGravSprite::Collided(const CCanvas &canvas,
				  const CVector2 &pos) const {
  return mCollision.Collided(canvas, int(pos.GetX()) - GetWidth()/2,
			     int(pos.GetY() - GetHeight()/2));
}



bool CGravSprite::Collided(const CCanvas& canvas, const CGravSprite& sprite,
			   const CVector2& pos1, const CVector2& pos2) const {
  return mCollision.Collided(canvas, sprite.mCollision,
			     int(pos1.GetX()) - GetWidth()/2,
			     int(pos1.GetY()) - GetHeight()/2,
			     int(pos2.GetX()) - sprite.GetWidth()/2,
			     int(pos2.GetY()) - sprite.GetHeight()/2);

}
