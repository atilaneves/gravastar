#ifndef CCLIENT_MENU_HPP_
#define CCLIENT_MENU_HPP_


class CGravMenu;
class CVersusMenu;
#include "CCursorMenu.hpp"
#include "CStringMenu.hpp"
#include "CFont.hpp"
#include "CGravOptions.hpp"
#include "CTcpClient.hpp"
#include <deque>


class CClientMenu: public CCursorMenu<CStringMenu> {
public:

    CClientMenu(const CSprite *cursorSprite, CGravMenu& gravMenu);
    virtual void Run(CRootMenu &rootMenu) override;
    void PrintCentre(const std::string& str) const;

private:

    CVersusMenu& mVersusMenu;
    CFont mFont;
};


std::string nextOption(std::deque<std::string>& strings);

#endif
