#include "CMenuCursor.hpp"
#include "CMenu.hpp"
#include "CSprite.hpp"
#include "CSound.hpp"


int CMenuCursor::sNbCursors = 0;
CSound* CMenuCursor::sSelectSound = 0;
CSound* CMenuCursor::sCancelSound = 0;


CMenuCursor::CMenuCursor(CMenu &menu, const CSprite *sprite):
  mRow(0), mCol(0), mMenu(menu), mSprite(sprite),
  mInput(new CMenuInput) {

  mMenu.AddCursor(this);
  sNbCursors++;
  if(!sSelectSound) sSelectSound = new CSound("select");
  if(!sCancelSound) sCancelSound = new CSound("cancel");
}


CMenuCursor::~CMenuCursor() {
  sNbCursors--;
  if(!sNbCursors) {
    delete sSelectSound; sSelectSound = 0;
    delete sCancelSound; sCancelSound = 0;
  }
}


CMenu* CMenuCursor::Update(CRootMenu &rootMenu) {

  if(mInput->Up())   --mRow;
  if(mInput->Down()) ++mRow;

  if(mInput->Left()) {
    if(mMenu.GetNbCols() > 1) --mCol;
    else GetSubMenu().Left();
  }

  if(mInput->Right()) { 
    if(mMenu.GetNbCols() > 1) ++mCol;
    else GetSubMenu().Right();
  }

  if(mRow.ToInt() >= int(mMenu.GetNbRows(mCol.ToInt())))
    mRow = mMenu.GetNbRows(mCol.ToInt()) - 1;
  if(mCol.ToInt() >= int(mMenu.GetNbCols())) mCol = mMenu.GetNbCols() - 1;

  if(mInput->Select()) {
    sSelectSound->PlayCentre();
    OnSelect();
    GetSubMenu().Run(rootMenu);
  }

  if(mInput->Cancel()) {
    sCancelSound->PlayCentre();
    return 0; //leaving menu
  }
  else
    return &mMenu; //all ok
}


void CMenuCursor::Draw(CCanvas &canvas) {
  DrawPointee(canvas);
  if(mSprite) DrawSprite(canvas);
}


void CMenuCursor::DrawPointee(CCanvas &canvas) {
  int x = mMenu.GetSubMenuX(mCol.ToInt());
  int y = mMenu.GetSubMenuY(mRow.ToInt());
  bool highlight = true;
  GetSubMenu().DrawIcon(canvas, x, y, highlight);
}


void CMenuCursor::DrawSprite(CCanvas &canvas) {

  int x = mMenu.GetSubMenuX(mCol.ToInt()) - mSprite->GetWidth() - 10;
  int y = mMenu.GetSubMenuY(mRow.ToInt()) + mMenu.GetHeight()/2 - 
    mSprite->GetHeight()/2;

  mSprite->Draw(canvas, x, y);
}


void CMenuCursor::SetRowsCols() {
  mRow.SetMax(mMenu.GetNbRows(mCol.ToInt()) - 1);
  mCol.SetMax(mMenu.GetNbCols() - 1);
}


CMenu& CMenuCursor::GetSubMenu() {
  return *mMenu.GetSubMenu(mCol.ToInt(), mRow.ToInt());
}
