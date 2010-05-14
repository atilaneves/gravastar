#ifndef CNULLBACKGROUND_H
#define CNULLBACKGROUND_H


#include "CMenuBackground.hpp"


class CNullBackground:public CMenuBackground {

public:

  CNullBackground() { }
  virtual ~CNullBackground() { }

  virtual void Draw(CCanvas &canvas) { }
  virtual void NewCanvas(int width, int height) { }


private:

};

#endif
