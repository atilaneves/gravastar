#ifndef CCLIENT_MENU_HPP_
#define CCLIENT_MENU_HPP_


class CGravMenu;
class CVersusMenu;
#include "CCursorMenu.hpp"
#include "CStringMenu.hpp"
#include "CFont.hpp"
#include "CGravOptions.hpp"


class CClientMenu: public CCursorMenu<CStringMenu> {
public:

    CClientMenu(const CSprite *cursorSprite, CGravMenu& gravMenu);
    virtual void Run(CRootMenu &rootMenu) override;
    void PrintCentre(const std::string& str);

private:

    CVersusMenu& mVersusMenu;
    CFont mFont;

    CGravOptions GetGravOptions() const;
};

#endif
