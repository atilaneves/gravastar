#ifndef CGRAVMENU_H
#define CGRAVMENU_H


#include "CSprite.hpp"
#include "CRootMenu.hpp"
#include "CSound.hpp"
#include "CPilotOptions.hpp"
#include "CFont.hpp"
#include <memory>
class CVersusMenu;
class COptionsMenu;
class CClientOptions;
class CGravOptions;


class CGravMenu: public CRootMenu {

public:

    CGravMenu(const CGravOptions &options);

    CClientOptions GetClientOptions(int nbPilots) const;
    CVersusMenu&   GetVersusMenu() { return *mVersusMenu; }
    const CSprite& GetCursorSprite() const { return *mCursorSprite; }

private:

    std::unique_ptr<CSprite> mCursorSprite;
    CSound                   mTitle;

    CVersusMenu*             mVersusMenu;
    COptionsMenu*            mOptionsMenu;
    CFont                    mAdFont;

    virtual void AtExit();
    virtual void BeforeMenu();

};


#endif
