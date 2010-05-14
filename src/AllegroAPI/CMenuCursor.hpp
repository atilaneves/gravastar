#ifndef CMENUCURSOR_HPP
#define CMENUCURSOR_HPP


class CMenu;
class CRootMenu;
class CCanvas;
class CSprite;
class CSound;
#include "CMenuInput.hpp"
#include "CIntWrap.hpp"
#include <memory>


class CMenuCursor {

public:

  CMenuCursor(CMenu &mMenu, const CSprite *mSprite = 0);
  virtual ~CMenuCursor();

          void   AdoptInput(CMenuInput *input) { mInput.reset(input); }
  virtual void   Draw(CCanvas &canvas);
  	  int    GetCol() const { return mCol.ToInt(); }
  	  int    GetNbCols() const { return mCol.GetMax(); }
  	  int    GetNbRows() const { return mRow.GetMax(); }
  	  int    GetRow() const { return mRow.ToInt(); }
  virtual void   OnSelect() { }
  	  void   SetCol(int c) { mCol = c; }
  	  void   SetRow(int r) { mRow = r; }
  	  void   SetRowsCols(); //sets total number of rows/columns
  virtual CMenu* Update(CRootMenu &rootMenu); //updates


protected:

  CIntWrap mRow, mCol; 
  CMenu   &mMenu;
  const CSprite *mSprite;
  std::auto_ptr<CMenuInput> mInput;

  static int sNbCursors;
  static CSound* sSelectSound;
  static CSound* sCancelSound;

  virtual void   DrawPointee(CCanvas &canvas);
  virtual void   DrawSprite(CCanvas &canvas);
          CMenu& GetSubMenu();

};


#endif
