#include "CServerMenu.hpp"
#include "CGravMenu.hpp"
#include "CVersusMenu.hpp"

CServerMenu::CServerMenu(const CSprite *cursorSprite, CGravMenu& gravMenu):
    CCursorMenu<CStringMenu>(cursorSprite, "Server"),
    mVersusMenu(gravMenu.GetVersusMenu()) {

    AddMenu(mVersusMenu);
}
