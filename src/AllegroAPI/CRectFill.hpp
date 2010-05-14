#ifndef RECTFILL_H
#define RECTFILL_H


class CCanvas;
#include "CScreenPos.hpp"


class CRectFill {

public:

  CRectFill(CCanvas &canvas, int x1, int y1, int x2, int y2, int colour);
  CRectFill(CCanvas &canvas, const CScreenPos &corner1,
	    const CScreenPos &corner2, int colour);


private:


};


#endif
