#include "CRect.hpp"
#include "CBitmap.hpp"
#include <allegro.h>


CRect::CRect(CBitmap &bitmap, int x1, int y1, int x2, int y2,
		     int colour) {
  rect((BITMAP*)bitmap.GetData() , x1, y1, x2, y2, colour);
}
