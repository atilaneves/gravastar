#include "CSpriteCollision.hpp"
#include "CCanvas.hpp"
#include "CColour.hpp"


CSpriteCollision::CSpriteCollision(BITMAP *bmp):
  mWidth(bmp->w), mHeight(bmp->h) {

}

positions_t CSpriteCollision::Collided(const CCanvas &canvas,
				      int x, int y) const {
  indices_t indices = GetIndices(canvas, x, y);
  positions_t positions;
  for(unsigned int i = 0; i < indices.size(); ++i) {
    int size = (int)positions.size();
    const int kMinDim = 80;
    if(size && mWidth < kMinDim && mHeight < kMinDim) return positions;
    int p = indices[i];
    if(size && IsLessThanMinDiff(p, positions[size - 1])) continue;
    positions.push_back(CScreenPos(x + mPixels[p].x, y + mPixels[p].y));
  }
  
  return positions;
}


bool CSpriteCollision::IsLessThanMinDiff(int p,
					 const CScreenPos& pos) const {
  const int kMinDiff = 10;
  return abs(mPixels[p].x - pos.GetX()) < kMinDiff &&
         abs(mPixels[p].y - pos.GetY()) < kMinDiff;
}


bool CSpriteCollision::Collided(const CCanvas &canvas,
				const CSpriteCollision& collision,
				int x1, int y1, int x2, int y2) const {
  indices_t indices = GetIndices(canvas, x1, y1);
  for(unsigned int i = 0; i < indices.size(); ++i) {
    int p = indices[i];
    if(collision.InSprite(x1 + mPixels[p].x -x2, y1 + mPixels[p].y - y2))
      return true;
  }

  return false;
}


indices_t CSpriteCollision::GetIndices(const CCanvas &canvas,
				       int x, int y) const {
  
  indices_t indices;
  bool chkBounds = x < mWidth  || x >= canvas.GetWidth() - mWidth ||
                   y < mHeight || y >= canvas.GetHeight() - mHeight;
  
  for(unsigned int p = 0; p < mPixels.size(); ++p) {
    if(chkBounds && OutOfBounds(canvas, x, y, p)) continue;
    if(IsPixelThere(canvas, x, y, p)) indices.push_back(p);
  }

  return indices;
}


bool CSpriteCollision::IsPixelThere(const CCanvas &canvas,
				    int x, int y, int p) const {
  return canvas.GetPixel(x + mPixels[p].x, y + mPixels[p].y) != 
    CColour::GetBlack();
}


bool CSpriteCollision::OutOfBounds(const CCanvas &canvas,
				   int x, int y, int p) const {
 return x < 0 || y < 0 || x + mPixels[p].x >= canvas.GetWidth() ||
        y+mPixels[p].y >= canvas.GetHeight();
}


bool CSpriteCollision::InSprite(int x, int y) const {

 for(unsigned int p = 0; p < mPixels.size(); ++p)
    if(mPixels[p].x == x && mPixels[p].y == y)
       return true;

 return false; //nope, no pixel here

}
