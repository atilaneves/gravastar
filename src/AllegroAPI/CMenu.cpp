#include "CMenu.hpp"
#include "CMenuIcon.hpp"
#include "CMenuCursor.hpp"
#include "CResolution.hpp"
#include "CRootMenu.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


CMenu::CMenu(CMenuIcon *icon):
    mIcon(icon), mMaxWidth(0), mMaxHeight(0) {

}


int CMenu::GetSubMenuX(int column) const {
    int deltaX = 0;
    int x      = CResolution::GetWidth() / 2;
    unsigned int nbColumns = mItems.size();

    if(nbColumns % 2 == 1) deltaX = -75; //odd
    return x - (nbColumns/2) * mMaxWidth + column * mMaxWidth + deltaX;
}


int CMenu::GetSubMenuY(int row) const {
    int y = (2*CResolution::GetHeight())/5;
    return y + (int)(row * 1.5 * mMaxHeight);
}


void CMenu::AddMenu(CMenuHolder&& menu, int col) {
    if((int)mItems.size() <= col) mItems.resize(col + 1); //add column if needed
    mItems[col].push_back(std::move(menu));
    CMenuIcon *icon = menu->mIcon.get();
    if (icon->GetWidth()  > mMaxWidth)  mMaxWidth  = icon->GetWidth();
    if (icon->GetHeight() > mMaxHeight) mMaxHeight = icon->GetHeight();
    for (auto &elem : mCursors)
      elem->SetRowsCols();
}


void CMenu::Run(CRootMenu &rootMenu) {
    if(!mCursors.size() && mItems.size()) { //has cursor or is leaf
        assert(mCursors.size());
        assert(!mItems.size());
    }
    if(!mItems.size() ||  !mItems[0].size()) return; //leaf node
    while(RunStep(rootMenu));
}


bool CMenu::RunStep(CRootMenu &rootMenu) {
    rootMenu.BeforeMenu();
    Draw(rootMenu.GetCanvas());
    bool active = IsActive(rootMenu);
    Update(rootMenu);
    rootMenu.AfterMenu();
    return active;
}


bool CMenu::IsActive(CRootMenu &rootMenu) {

    bool active = true;

    for (auto &elem : mCursors)
      if (!elem->Update(rootMenu))
        active = false;

    return active;
}


void CMenu::Draw(CCanvas &canvas) {

    for(unsigned int c = 0; c < mItems.size(); ++c)
        for(unsigned int r = 0; r < mItems[c].size(); ++r)
            mItems[c][r]->DrawIcon(canvas, GetSubMenuX(c), GetSubMenuY(r));

    for (auto &elem : mCursors)
      elem->Draw(canvas);
}


void CMenu::DrawIcon(CCanvas &canvas, int x, int y, bool highlight) {
    mIcon->Draw(canvas, x, y, highlight);
}
