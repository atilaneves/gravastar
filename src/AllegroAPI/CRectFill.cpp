#include "CRectFill.hpp"
#include "CCanvas.hpp"
#include <allegro.h>


CRectFill::CRectFill(CCanvas &canvas, int x1, int y1, int x2, int y2,
		     int colour) {
  rectfill((BITMAP*)canvas.GetData() , x1, y1, x2, y2, colour);
}


CRectFill::CRectFill(CCanvas &canvas, const CScreenPos &corner1,
		     const CScreenPos &corner2, int colour) {
  rectfill((BITMAP*)canvas.GetData() , corner1.GetX(), corner1.GetY(),
	   corner2.GetX(), corner2.GetY(), colour);
}
