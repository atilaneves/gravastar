#ifndef CERASEABLE_H
#define CERASEABLE_H


class CCanvas;


class CEraseable {

public:

  virtual void Erase(CCanvas &canvas, int x, int y) const = 0;


private:



};


#endif
