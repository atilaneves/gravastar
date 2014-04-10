#ifndef CLEVELGFX_H
#define CLEVELGFX_H

#include "CColour.hpp"
#include "CCanvas.hpp"
#include "CScreenPos.hpp"
#include "CVector2.hpp"
class CPilot;


class CLevelGfx {

public:

  CLevelGfx(const CCanvas &canvas);

  float FindEdge(CScreenPos pos) const;
  bool  IsClearLine(float x1,float y1,float x2,float y2,int step=5) const;
  bool  IsClearLine(const CVector2& pos1, const CVector2& pos2,
		    int step=5) const;
  bool  IsFreeSquare(int xc,int yc,int side = 5) const;

 //inlines
  bool BlackPixel(int x,int y) const {
    //int p=mCanvas.GetPixel(x,y);
    //return p==CColour::GetBlack() || p<0; }
    return mCanvas.GetPixel(x,y) == 0; }


private:

  const CCanvas& mCanvas;

};


#endif
