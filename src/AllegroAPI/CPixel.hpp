#ifndef CPIXEL_H
#define CPIXEL_H


#include "CDrawable.hpp"


class CPixel: public CDrawable {

public:

  CPixel(int colour):mColour(colour) { }
  virtual void Draw (CCanvas &canvas, int x, int y) const override;
  virtual void Erase(const CCanvas &canvas, int x, int y);


private:

  int mColour;

};

#endif
