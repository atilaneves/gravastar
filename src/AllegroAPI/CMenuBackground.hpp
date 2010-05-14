#ifndef CMENUBACKGROUND_H
#define CMENUBACKGROUND_H


class CCanvas;


class CMenuBackground {

public:

  CMenuBackground() { }
  virtual ~CMenuBackground() { }

  virtual void Draw(CCanvas &canvas) = 0;
  virtual void NewCanvas(int width, int height) = 0;


private:

};

#endif
