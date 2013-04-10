#ifndef CLEVELMENU_H
#define CLEVELMENU_H


#include "CStringMenu.hpp"
#include "CMenuCursor.hpp"
#include "CGravOptions.hpp"
#include "CLevelCounter.hpp"
#include "CSound.hpp"
#include <vector>
class CVersusMenu;
class CMeleeStart;
class CLevelMenuSprite;
class CSprite;
class CVersusMenu;


class CLevelMenu: public CStringMenu {

public:

  CLevelMenu(const CVersusMenu &versusMenu);
  ~CLevelMenu();

  virtual void Draw(CCanvas &canvas);
  CGravOptions GetOptions() const;
          int  GetLevelNb() const;
  virtual void Run(CRootMenu &rootMenu);


private:

  CLevelCounter mLevelCounter;
  CMenuCursor mCursor;
  CSound mSound;
  CMeleeStart* mMeleeStart;
  std::vector<CLevelMenuSprite*> mSprites;

  const CLevelMenuSprite& GetSprite() const;
  virtual int GetSubMenuX(int column) const;
  virtual int GetSubMenuY(int row) const;

};


#endif
