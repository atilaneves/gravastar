#ifndef CNULLBACKGROUND_H
#define CNULLBACKGROUND_H


#include "CMenuBackground.hpp"


class CNullBackground:public CMenuBackground {

public:

  CNullBackground() { }
  virtual ~CNullBackground() { }

  virtual void Draw(CCanvas &canvas) override {}
  virtual void NewCanvas(int width, int height) override {}

private:

};

#endif
