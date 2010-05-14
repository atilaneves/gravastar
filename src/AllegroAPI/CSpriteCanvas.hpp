#ifndef CSPRITECANVAS_H
#define CSPRITECANVAS_H


#include "CCanvas.hpp"


class CSpriteCanvas: public CCanvas {

public:

  CSpriteCanvas(void *data);
  CSpriteCanvas(const CBitmap& bitmap);
  CSpriteCanvas(int w, int h);

  void Clear();


private:

  void Constructor(void *data);

};

#endif
