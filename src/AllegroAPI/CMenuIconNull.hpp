#ifndef CMENUICONNULL_H
#define CMENUICONNULL_H


#include "CMenuIcon.hpp"


class CMenuIconNull: public CMenuIcon {

public:

  CMenuIconNull() { }
  virtual ~CMenuIconNull() {}

  virtual void Draw(CCanvas &canvas, int x, int y, bool highlight) {} 
  virtual int  GetHeight() const { return 0; }
  virtual int  GetWidth()  const { return 0; }


private:



};


#endif
