#ifndef CCLIENT_MENU_HPP_
#define CCLIENT_MENU_HPP_


class CGravMenu;
class CGravOptions;
class CVersusMenu;
#include "CCursorMenu.hpp"
#include "CStringMenu.hpp"


class CClientMenu: public CCursorMenu<CStringMenu> {
public:

    CClientMenu(const CSprite *cursorSprite, CGravMenu& gravMenu);
    virtual void Run(CRootMenu &rootMenu) override;

private:

    CVersusMenu& mVersusMenu;
};

#endif
