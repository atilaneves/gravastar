#ifndef CCLIENT_MENU_HPP_
#define CCLIENT_MENU_HPP_


class CGravMenu;
class CVersusMenu;
#include "CCursorMenu.hpp"
#include "CStringMenu.hpp"
#include "CFont.hpp"
#include "CGravOptions.hpp"
#include "CTcpClient.hpp"


class CClientMenu: public CCursorMenu<CStringMenu> {
public:

    CClientMenu(const CSprite *cursorSprite, CGravMenu& gravMenu);
    virtual void Run(CRootMenu &rootMenu) override;

private:

    CVersusMenu& mVersusMenu;
    CFont mFont;

    CGravOptions GetGravOptions(std::vector<std::string>& options) const;
    void StartMeleeClient(CRootMenu &rootMenu, std::vector<std::string>& options) const;
    void PrintCentre(const std::string& str) const;
};

#endif
