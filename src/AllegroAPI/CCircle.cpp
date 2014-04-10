#include "CCircle.hpp"
#include "CBitmap.hpp"
#include <allegro.h>


CCircle::CCircle(CBitmap& bmp, int x, int y, int radius, int colour) {
  circle((BITMAP*)bmp.GetData(), x, y, radius, colour);
}
