#ifndef CSHIPMENU_H
#define CSHIPMENU_H


#include "CStringMenu.hpp"
#include "CSound.hpp"
#include "CLevelMenu.hpp"
#include "CScreenPos.hpp"
class CShipMenuCursor;
class CShipMenuItem;
class CVersusMenu;

typedef std::vector<std::vector<std::string> > shipsTypes_t;
typedef std::vector<CMenuCursor*>::iterator cursorPlace_t;
typedef std::vector<CScreenPos> cursorsPos_t;

class CShipMenu: public CStringMenu {

public:

  enum { kMaxNbPilots = 4 };

  CShipMenu(const CGravMenu &gravMenu, const CVersusMenu &versusMenu);
  virtual ~CShipMenu();

          int         GetLevelNb() const { return mLevelMenu.GetLevelNb(); }
          std::string GetShipType(int p, int s) const;
  const shipTypes_t&  GetShipTypes(int p) const { return mShipTypes[p]; }
  virtual void        Run(CRootMenu &rootMenu);


private:

  CSound mSound;
  const CGravMenu &mGravMenu;
  const CVersusMenu &mVersus;
  std::vector<CShipMenuItem*> mShipItems;
  shipsTypes_t mShipTypes;
  CLevelMenu mLevelMenu;
  cursorsPos_t mCursorsPos;

  void Clear();
  void CreateCursors();
  int  GetSubMenuX(int column) const;
  int  GetSubMenuY(int row)    const;
  void RemoveDormantCursors();
  bool IsAllDone() const;

};


#endif
