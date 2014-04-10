#include "CLevelGfx.hpp"
#include "CVector2.hpp"
#include <math.h> //M_PI



CLevelGfx::CLevelGfx(const CCanvas &canvas):
   mCanvas(canvas) {

}


float CLevelGfx::FindEdge(CScreenPos pos) const {
 //simple version, only looks for horizontal or vertical edges
  int x = pos.GetX(); int y = pos.GetY();
  int rightX = x + 1;
  int leftX  = x - 1;
  int upY    = y - 1;
  int downY  = y + 1; //y is inverted

  //return angle of vector pointing outwards from edge
  do {
    if(BlackPixel(x, upY))    return 1.5*M_PI; //hit horizontal edge below
    if(BlackPixel(rightX, y)) return 0;        //hit vertical edge to its left
    if(BlackPixel(leftX, y))  return M_PI;     //hit vertical edge to its right
    if(BlackPixel(x, downY))  return M_PI/2;   //hit horizontal edge above

    leftX--; if(leftX < 0) leftX = 0;

    rightX++;
    if(rightX >= mCanvas.GetWidth())
      rightX = mCanvas.GetWidth() - 1;

    upY--; if(upY < 0) upY = 0;

    downY++;
    if(downY >= mCanvas.GetHeight())
      downY = mCanvas.GetHeight() - 1;
  } while(true);

  return 0; //never gets here
}


bool CLevelGfx::IsFreeSquare(int xc, int yc, int side) const {

  int x0 = xc - side/2;
  int y0 = yc - side/2;
  int x1 = xc + side/2;
  int y1 = yc + side/2;

  if(x0 < 0) x0=0;
  if(y0 < 0) y0=0;
  if(x1 > mCanvas.GetWidth())  x1 = mCanvas.GetWidth();
  if(y1 > mCanvas.GetHeight()) y1 = mCanvas.GetHeight();

  for(int y = y0; y < y1; y += side) //y 1st makes gfx faster
    for(int x = x0; x < x1; x += side)
      if(!BlackPixel(x,y)) return false;

  return true; //nth here!
}


static int gDim(float x, int dim) {
 if(x < 0) x = 0; if(x >= dim) x = dim - 1;
 return int(x);
}


bool CLevelGfx::IsClearLine(float x1,float y1,
			    float x2,float y2,int step) const {

  CVector2 pos1(gDim(x1, mCanvas.GetWidth()), gDim(y1, mCanvas.GetHeight()));
  CVector2 pos2(gDim(x2, mCanvas.GetWidth()), gDim(y2, mCanvas.GetHeight()));
  CVector2 dPos = pos2 - pos1;
  float dist = dPos.Radius();
  dPos *= step/dist; //measures step now
  float stepCmp = step + 0.25;

  //chk pixels in the space between us and them
  while(dist > stepCmp) {
    pos1 += dPos;
    dist -= step;
    if(!BlackPixel((int)pos1.GetX(), (int)pos1.GetY())) return false;
 }

  return true; //nth in the way
}


bool CLevelGfx::IsClearLine(const CVector2& pos1, const CVector2& pos2,
			    int step) const {
  int x1 = int(pos1.GetX());
  int y1 = int(pos1.GetY());
  int x2 = int(pos2.GetX());
  int y2 = int(pos2.GetY());
  return IsClearLine(x1, y1, x2, y2, step);
}
