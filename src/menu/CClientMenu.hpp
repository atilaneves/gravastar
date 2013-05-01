#ifndef CCLIENT_MENU_HPP_
#define CCLIENT_MENU_HPP_


#include "CCursorMenu.hpp"
#include "CStringMenu.hpp"
#include "CGravOptions.hpp"


class CClientMenu: public CCursorMenu<CStringMenu> {
public:

    CClientMenu(const CSprite *cursorSprite);
    virtual void Run(CRootMenu &rootMenu) override;

    void SetGravOptions(const CGravOptions& o) { mGravOptions = o; }

private:

    CGravOptions mGravOptions;
};

#endif
