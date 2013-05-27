#ifndef CSERVER_MENU_HPP_
#define CSERVER_MENU_HPP_


class CGravMenu;
class CVersusMenu;
#include "CCursorMenu.hpp"
#include "CStringMenu.hpp"


class CServerMenu: public CCursorMenu<CStringMenu> {
public:

    CServerMenu(const CSprite *cursorSprite, CGravMenu& gravMenu);

private:

    CVersusMenu& mVersusMenu;
};

#endif
