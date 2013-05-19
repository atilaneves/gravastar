#include "CSprite.hpp"
#include "CCanvas.hpp"
#include "CColour.hpp"
#include "pi.hpp"


CSprite::CSprite(void *data):
    mData(get_rle_sprite(static_cast<BITMAP*>(data))) {

}


CSprite::CSprite(void *data, float angle, float scale) {
    auto bitmap = CreateBitmap(data, angle, scale);
    mData = get_rle_sprite(bitmap); //get what we just drew
    destroy_bitmap(bitmap);
}


CSprite::~CSprite() {
    destroy_rle_sprite(mData);
}


BITMAP* CSprite::CreateBitmap(void *data, float angle, float scale) {
    auto sprite = static_cast<BITMAP*>(data);
    if(angle == 0 && scale == 1) return(MakeTransparent(sprite));
    int fixangle = itofix( 256 - (int) ((angle/M_PI)*128) ); //convert
    int fixscale = ftofix(scale);
    auto rotated = create_bitmap(sprite->w, sprite->h);
    clear_to_color(rotated, bitmap_mask_color(sprite)); //clean to draw on
    rotate_scaled_sprite(rotated, sprite, 0, 0, fixangle, fixscale); //rotates spr
    return(MakeTransparent(rotated));
}


BITMAP* CSprite::MakeTransparent(BITMAP* sprite) { //black to transparent
    for(int x = 0; x < sprite->w; ++x) {     //loop through the bitmap
        for(int y = 0; y < sprite->h; ++y) {
            if(getpixel(sprite, x, y) == CColour::GetBlack())
                putpixel(sprite, x, y, bitmap_mask_color(sprite));
        }
    }

    return(sprite);
}


void CSprite::Draw(CCanvas &canvas, int x, int y) const {
    draw_rle_sprite(static_cast<BITMAP*>(canvas.GetData()), mData, x, y);
}
