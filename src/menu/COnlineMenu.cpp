#include "COnlineMenu.hpp"
#include "CServerMenu.hpp"
#include "CClientMenu.hpp"

COnlineMenu::COnlineMenu(const CSprite* cursorSprite, CGravMenu& gravMenu):
    CCursorMenu<CStringMenu>(cursorSprite, "Online") {

    AddMenu(new CServerMenu(cursorSprite, gravMenu));
    AddMenu(new CClientMenu(cursorSprite));
}
