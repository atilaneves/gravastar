#ifndef CSUBCANVAS_H
#define CSUBCANVAS_H


#include "CBitmap.hpp"
class CCanvas;


class CSubCanvas: public CBitmap {

public:

  CSubCanvas(const CCanvas &canvas, int x, int y, int width, int height);
  CSubCanvas(const CSubCanvas &subCanvas);


private:

  const CCanvas *mMainCanvas;
  int mX, mY, mWidth, mHeight;

};

#endif
