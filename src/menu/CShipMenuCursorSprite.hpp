#ifndef CMENU_CURSOR_SHIP_SPRITE_H
#define CMENU_CURSOR_SHIP_SPRITE_H


class CGravSprite;
class CTeam;


class CShipMenuCursorSprite {

public:

 static CGravSprite *CreateSprite(int index, const CTeam &team);

};

#endif
