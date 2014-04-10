#ifndef CSPRITE_H
#define CSPRITE_H

#include "CDrawable.hpp"
#include <allegro.h>


class CSprite: public CDrawable {

public:

    CSprite(void *data);
    CSprite(void *data, float angle, float scale = 1);
    virtual ~CSprite();

    static  BITMAP* CreateBitmap(void *data, float angle, float scale);
    virtual void Draw(CCanvas &canvas, int x, int y) const override;
    int GetHeight() const override { return mData->h; }
    int GetWidth() const override { return mData->w; }

private:

    typedef RLE_SPRITE SpriteImp_t; //data structure used to represent sprite
    SpriteImp_t *mData; //the actual sprite data

    static BITMAP* MakeTransparent(BITMAP* sprite);
};

#endif
