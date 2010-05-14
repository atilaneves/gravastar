#ifndef CGRAVMENU_H
#define CGRAVMENU_H


#include "CSprite.hpp"
#include "CRootMenu.hpp"
#include "CSound.hpp"
#include "CPilotOptions.hpp"
#include "CFont.hpp"
#include <memory>
class CGravOptions;
class CClientOptions;
class CMeleeStart;
class CVersusMenu;
class COptionsMenu;


class CGravMenu: public CRootMenu {

public:

  CGravMenu(const CGravOptions &options);

  CGravOptions   GetGravOptions() const;


private:

  std::auto_ptr<CSprite> mCursorSprite;
  CSound                 mTitle;
  CVersusMenu*           mVersusMenu;
  COptionsMenu*          mOptionsMenu;
  CFont                  mAdFont;

  virtual void AtExit();
  virtual void BeforeMenu();

};


#endif
