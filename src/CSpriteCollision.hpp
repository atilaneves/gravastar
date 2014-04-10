#ifndef CSPRITECOLLISION_H
#define CSPRITECOLLISION_H


#include "CScreenPos.hpp"
#include <allegro.h>
#include <vector>
class CCanvas;


typedef std::vector<int> indices_t ;
typedef std::vector<CScreenPos> positions_t;


class CSpriteCollision {

public:

  struct SSpritePixel {
    SSpritePixel(int xx,int yy):x(xx),y(yy) {}
    int x,y;
  };

  CSpriteCollision(BITMAP *bmp);

  positions_t Collided(const CCanvas &canvas, int x, int y) const;
  bool        Collided(const CCanvas &canvas,
		       const CSpriteCollision& collision,
		       int x1, int y1, int x2, int y2) const;
  bool        InSprite(int x, int y) const;
  void        push_back(const SSpritePixel &p) { mPixels.push_back(p); }
  

private:

  int mWidth, mHeight;
  std::vector<SSpritePixel> mPixels;

  indices_t GetIndices(const CCanvas &canvas, int x, int y) const;
  bool      IsLessThanMinDiff(int p, const CScreenPos& pos) const;
  bool      IsPixelThere(const CCanvas &canvas, int x, int y, int p) const;
  bool      OutOfBounds(const CCanvas &canvas,int x, int y, int p) const;

};


#endif
