#ifndef CSPRITEMENUBKG_H
#define CSPRITEMENUBKG_H


#include "CMenuBackground.hpp"
class CSprite;


class CSpriteMenuBkg: public CMenuBackground {

public:

  CSpriteMenuBkg(CSprite &sprite, int x, int y);
  virtual ~CSpriteMenuBkg() { }

  virtual void Draw(CCanvas &canvas);


private:

 CSprite &mSprite;
 int      mX, mY;

};

#endif
