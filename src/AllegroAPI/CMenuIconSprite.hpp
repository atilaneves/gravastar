#ifndef CMENU_ICON_SPRITE_H
#define CMENU_ICON_SPRITE_H


#include "CMenuIcon.hpp"
class CSprite;


class CMenuIconSprite:public CMenuIcon {

public:

 CMenuIconSprite(CSprite &sprite);
 virtual ~CMenuIconSprite() { }

 virtual void Draw(CCanvas &canvas, int x, int y, bool highlight = false) const override;
 virtual int GetHeight() const override;
 virtual int GetWidth() const override;

protected:

 CSprite &mSprite;

};

#endif
