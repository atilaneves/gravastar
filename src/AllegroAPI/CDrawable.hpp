#ifndef CDRAWABLE_H
#define CDRAWABLE_H


class CCanvas;


class CDrawable {

public:

  virtual void Draw(CCanvas &canvas, int x, int y) const = 0;
  virtual int  GetHeight() const = 0;
  virtual int  GetWidth()  const = 0;



private:



};


#endif
