#ifndef CROOTMENU_H
#define CROOTMENU_H


class CFont;
class CSprite;
#include "CCanvas.hpp"
#include "CMenu.hpp"
#include "CMenuCursor.hpp"
#include "CMenuBackground.hpp"
#include "CFont.hpp"
#include "CSong.hpp"
#include <vector>
#include <memory>



class CRootMenu {

public:

  CRootMenu(bool windowed, int screenWidth, int screenHeight,
	    const CFont &font, CSprite *cursorSprite);
  virtual ~CRootMenu() { }

  void 	   AfterMenu();
  void 	   AdoptBackground(CMenuBackground *b) { mBackground.reset(b); }
  void 	   AddMenu(CMenu *menu);
  void 	   AdoptSong(CSong *s)    { mSong.reset(s); mSong->PlayLoop(); }
  void 	   AdoptTitle(CMenuBackground *b)      { mTitle.reset(b);      }
  virtual void BeforeMenu();
  CCanvas& GetCanvas() const { return *mCanvas; }
  void 	   PlaySong() { if(mSong.get()) mSong->PlayLoop(); }
  void 	   NewCanvas(int w, int h);
  void 	   Run();
  void 	   StopSong() { if(mSong.get()) mSong->Stop(); }


protected:

  std::auto_ptr<CCanvas>         mCanvas;


private:

  CMenu                          mMenu;
  CMenuCursor                    mCursor;
  CFont                          mFont;
  std::vector<CMenu*>            mMenus;
  std::auto_ptr<CMenuBackground> mTitle;
  std::auto_ptr<CMenuBackground> mBackground;
  std::auto_ptr<CSong>           mSong;

  virtual void AtExit() { }
          bool Exit();

};



#endif
