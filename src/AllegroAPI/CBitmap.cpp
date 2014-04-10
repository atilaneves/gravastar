#include "CBitmap.hpp"
#include "CColour.hpp"


CBitmap::CBitmap(BitmapImp_t *data):
  mData(data) {

}


CBitmap::~CBitmap() {
  if(mData != screen) destroy_bitmap(mData);
}


BitmapImp_t* CBitmap::CopyBitmap(void *data) {
  BitmapImp_t *bmp=(BitmapImp_t*)data;
  int w = bmp->w;
  int h = bmp->h;
  BitmapImp_t *newData = create_bitmap(w, h);
  blit(bmp, newData, 0, 0, 0, 0, w, h); //copy the data here
  return(newData);
}


void CBitmap::Clear(int colour) {
  if(colour < 0) colour = bitmap_mask_color(mData);
  clear_to_color(mData, colour);
}


void CBitmap::Draw(const CBitmap &bitmap, int x, int y, int fixAngle) {
  if(!fixAngle) //no rotation
    draw_sprite((BITMAP*)bitmap.GetData(), mData, x, y);
  else
    rotate_sprite((BITMAP*)bitmap.GetData(), mData, x, y, fixAngle);
}


void CBitmap::Blit(CBitmap &bitmap,
		   int x0,int y0,int x1,int y1,int w,int h) const {
  blit(mData,(BITMAP*)bitmap.GetData(), x0, y0, x1, y1, w, h);
}


void CBitmap::Blit(CBitmap &bitmap, int x1, int y1) const {
  Blit(bitmap, 0, 0, x1, y1, GetWidth(), GetHeight());
}


void CBitmap::MaskBlit(CBitmap &bitmap,
		     int x0,int y0,int x1,int y1,int w,int h) const {
  masked_blit(mData, (BITMAP*)bitmap.GetData(), x0, y0, x1, y1, w, h);
}


void CBitmap::Flip(int x,int y) const { //flip it to the screen
  blit(mData, screen, x, y, 0, 0, SCREEN_W, SCREEN_H);
}


int CBitmap::GetMask() const {
  return bitmap_mask_color(mData);
}


void CBitmap::StretchBlit(CBitmap &bitmap, int x, int y, int w, int h) const {
  stretch_blit(mData, bitmap.mData, 0, 0, GetWidth(), GetHeight(),
	       x, y, w, h);
}
