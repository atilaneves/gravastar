#ifndef CSPRITE_H
#define CSPRITE_H


#include "CDrawable.hpp"
#include <allegro.h>


typedef RLE_SPRITE SpriteImp_t; //data structure used to represent sprite


class CSprite: public CDrawable {

public:

  CSprite(void *data);
  CSprite(void *data, float angle, float scale = 1);
  virtual ~CSprite();

  static  BITMAP* CreateBitmap(void *data, float angle, float scale);
  virtual void    Draw (CCanvas &canvas, int x, int y) const;
          int     GetHeight() const { return mData->h; }
          int     GetWidth()  const { return mData->w; }


private:

  SpriteImp_t *mData; //the actual sprite data

  static BITMAP* MakeTransparent(BITMAP *sprite);

};

#endif
