#ifndef CMENU_H
#define CMENU_H


class CRootMenu;
class CMenuCursor;
class CCanvas;
#include "CMenuIcon.hpp"
#include <vector>
#include <memory>


class CMenu {

public:

  CMenu(CMenuIcon *icon);
  virtual ~CMenu();

           void AddMenu(CMenu *menu, int col=0);
           void AddCursor(CMenuCursor *c) { mCursors.push_back(c); }
           void AdoptIcon(CMenuIcon* i) { mIcon.reset(i); }
  virtual  void Draw(CCanvas &canvas);
  virtual  void DrawIcon(CCanvas &canvas, int x, int y, bool highlight=false);
           int  GetHeight()      const   { return mMaxHeight;       }
  unsigned int  GetNbCols()      const   { return mItems.size();    }
  unsigned int  GetNbRows(int c) const   { return mItems[c].size(); }
        CMenu*  GetSubMenu(int c, int r) { return mItems[c][r];     }
  virtual  int  GetSubMenuX(int column) const;
  virtual  int  GetSubMenuY(int row) const;
  virtual  void Left() { }
           int  GetWidth()       const   { return mMaxWidth;        }
  virtual  void Right() { }
  virtual  void Run(CRootMenu &rootMenu);
  virtual  void Update(CRootMenu &rootMenu) { }
 

protected:

  virtual bool IsActive(CRootMenu &rootMenu);
          bool RunStep(CRootMenu &rootMenu);

  std::auto_ptr<CMenuIcon>          mIcon;
  int                               mMaxWidth, mMaxHeight;
  std::vector <CMenuCursor*>        mCursors;
  std::vector<std::vector<CMenu*> > mItems;


};

#endif
