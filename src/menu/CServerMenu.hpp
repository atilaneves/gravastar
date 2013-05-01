#ifndef CSERVER_MENU_HPP_
#define CSERVER_MENU_HPP_


class CGravMenu;
#include "CCursorMenu.hpp"
#include "CStringMenu.hpp"


class CServerMenu: public CCursorMenu<CStringMenu> {
public:

    CServerMenu(const CSprite *cursorSprite, CGravMenu& gravMenu);
};

#endif
