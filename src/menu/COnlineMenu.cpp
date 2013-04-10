#include "COnlineMenu.hpp"
#include "CServerMenu.hpp"


COnlineMenu::COnlineMenu(const CSprite* cursorSprite, const CGravMenu& gravMenu):
    CCursorMenu<CStringMenu>(cursorSprite, "Online") {

    AddMenu(new CServerMenu(cursorSprite, gravMenu));
    AddMenu(new CStringMenu("Client"));
}
