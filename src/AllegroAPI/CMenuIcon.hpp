#ifndef CMENUICON_H
#define CMENUICON_H


class CCanvas;


class CMenuIcon {

public:

  virtual void Draw(CCanvas &canvas, int x, int y, bool highlight) const = 0;
  virtual int  GetHeight() const=0;
  virtual int  GetWidth()  const=0;


private:



};


#endif
