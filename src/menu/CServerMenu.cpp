#include "CServerMenu.hpp"
#include "CVersusMenu.hpp"

CServerMenu::CServerMenu(const CSprite *cursorSprite, const CGravMenu& gravMenu):
    CCursorMenu<CStringMenu>(cursorSprite, "Server") {

    AddMenu(new CVersusMenu(cursorSprite, gravMenu, "Start"));
}
