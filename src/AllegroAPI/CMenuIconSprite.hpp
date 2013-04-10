#ifndef CMENU_ICON_SPRITE_H
#define CMENU_ICON_SPRITE_H


#include "CMenuIcon.hpp"
class CSprite;


class CMenuIconSprite:public CMenuIcon {

public:

 CMenuIconSprite(CSprite &sprite);
 virtual ~CMenuIconSprite() { }
 
 virtual void Draw(CCanvas &canvas, int x, int y, bool highlight = false) const override;
 virtual int  GetHeight() const;
 virtual int  GetWidth()  const;


protected:

 CSprite &mSprite;

};

#endif
