#include "CLine.hpp"
#include "CBitmap.hpp"
#include <allegro.h>


CLine::CLine(CBitmap &bmp, int x1,int y1,int x2,int y2,int col) {
  line((BITMAP*)bmp.GetData(),x1,y1,x2,y2,col);
}
