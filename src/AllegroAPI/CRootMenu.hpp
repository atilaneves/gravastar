#ifndef CROOTMENU_H
#define CROOTMENU_H


#include "CSongPlayer.hpp"
#include "CCanvas.hpp"
#include "CMenu.hpp"
#include "CMenuCursor.hpp"
#include "CMenuBackground.hpp"
#include "CFont.hpp"
#include "CSong.hpp"
#include <vector>
#include <memory>
class CFont;
class CSprite;


class CRootMenu: public CSongPlayer {

public:

    CRootMenu(bool windowed, int screenWidth, int screenHeight,
              const CFont &font, CSprite *cursorSprite);
    virtual ~CRootMenu() { }

    void         AfterMenu();
    void         AdoptBackground(CMenuBackground *b) { mBackground.reset(b); }
    void         AddMenu(CMenu *menu);
    void         AdoptSong(CSong *s)    { mSong.reset(s); mSong->PlayLoop(); }
    void         AdoptTitle(CMenuBackground *b)      { mTitle.reset(b);      }
    virtual void BeforeMenu();
    CCanvas&     GetCanvas() const { return *mCanvas; }
    virtual void PlaySong() override { if(mSong.get()) mSong->PlayLoop(); }
    void         NewCanvas(int w, int h);
    void         Run();
    virtual void StopSong() override { if(mSong.get()) mSong->Stop(); }

protected:

    std::unique_ptr<CCanvas> mCanvas;

private:

    CMenu                            mMenu;
    CMenuCursor                      mCursor;
    CFont                            mFont;
    std::vector<CMenu*>              mMenus;
    std::unique_ptr<CMenuBackground> mTitle;
    std::unique_ptr<CMenuBackground> mBackground;
    std::unique_ptr<CSong>           mSong;

    virtual void AtExit() { }
    bool Exit();
};



#endif
