#ifndef CLEVELMENU_H
#define CLEVELMENU_H


#include "CStringMenu.hpp"
#include "CMenuCursor.hpp"
#include "CGravOptions.hpp"
#include "CLevelCounter.hpp"
#include "CSound.hpp"
#include "CLevelMenuSprite.hpp"
#include <vector>
#include <memory>
class CVersusMenu;
class CMeleeStart;
class CSprite;
class CVersusMenu;


class CLevelMenu: public CStringMenu {

public:

    CLevelMenu(const CVersusMenu &versusMenu);

    virtual void Draw(CCanvas &canvas) override;
    CGravOptions GetOptions() const;
    int  GetLevelNb() const;
    virtual void Run(CRootMenu &rootMenu) override;

private:

    CLevelCounter mLevelCounter;
    CMenuCursor mCursor;
    CSound mSound;
    CMeleeStart* mMeleeStart;
    std::vector<std::unique_ptr<CLevelMenuSprite>> mSprites;

    const CLevelMenuSprite& GetSprite() const;
    virtual int GetSubMenuX(int column) const override;
    virtual int GetSubMenuY(int row) const override;
};


#endif
