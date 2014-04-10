#ifndef CMENU_H
#define CMENU_H


class CRootMenu;
class CMenuCursor;
class CCanvas;
#include "CMenuIcon.hpp"
#include "CRefOrPointer.hpp"
#include <vector>
#include <memory>

class CMenu;
using CMenuHolder = CRefOrPointer<CMenu>;

class CMenu {

    friend class CMenuDecorator;

public:

    CMenu(CMenuIcon *icon);
    virtual ~CMenu() { }

             void AddMenu(CMenu *menu, int col=0) { AddMenu(CMenuHolder(menu), col); }
             void AddMenu(CMenu &menu, int col=0) { AddMenu(CMenuHolder(menu), col); }
             void AddCursor(CMenuCursor *c) { mCursors.push_back(c); }
             void AdoptIcon(CMenuIcon* i) { mIcon.reset(i); }
    virtual  void Draw(CCanvas &canvas);
    virtual  void DrawIcon(CCanvas &canvas, int x, int y, bool highlight=false);
             int  GetHeight()      const   { return mMaxHeight;       }
    unsigned int  GetNbCols()      const   { return mItems.size();    }
    unsigned int  GetNbRows(int c) const   { return mItems[c].size(); }
          CMenu*  GetSubMenu(int c, int r) { return static_cast<CMenu*>(mItems[c][r]); }
    virtual  int  GetSubMenuX(int column) const;
    virtual  int  GetSubMenuY(int row) const;
    virtual  void Left() { }
             int  GetWidth()       const   { return mMaxWidth;        }
    virtual  void Right() { }
    virtual  void Run(CRootMenu &rootMenu);
    virtual  void Update(CRootMenu &rootMenu) { }


protected:

            void AddMenu(CMenuHolder&& menu, int col = 0);
    virtual bool IsActive(CRootMenu &rootMenu);
            bool RunStep(CRootMenu &rootMenu);

    std::unique_ptr<CMenuIcon>       mIcon;
    int                              mMaxWidth, mMaxHeight;
    std::vector <CMenuCursor*>       mCursors;
    std::vector<std::vector<CMenuHolder>> mItems;
};

#endif
