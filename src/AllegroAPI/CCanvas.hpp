#ifndef CCANVAS_H
#define CCANVAS_H


#include "CBitmap.hpp"


typedef BitmapImp_t CanvasImp_t;

class CCanvas: public CBitmap {

public:

  CCanvas(void *data);
  CCanvas(int w, int h);
  CCanvas(const CBitmap &bitmap);
    
  CCanvas& operator=(const CCanvas &canvas);

  
private:
  CCanvas() : CBitmap(nullptr) {}
};

#endif
