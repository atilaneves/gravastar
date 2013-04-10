#ifndef CONLINEMENU_HPP_
#define CONLINEMENU_HPP_

class CGravMenu;
#include "CCursorMenu.hpp"
#include "CStringMenu.hpp"


class COnlineMenu: public CCursorMenu<CStringMenu> {
public:

    COnlineMenu(const CSprite *cursorSprite, CGravMenu& gravMenu);
};

#endif
