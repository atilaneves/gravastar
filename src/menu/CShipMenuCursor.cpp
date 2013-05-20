#include "CShipMenuCursor.hpp"
#include "CShipMenuCursorSprite.hpp"
#include "CGravSprite.hpp"
#include "CMenu.hpp"
#include "CShipMenuItem.hpp"
#include "CVersusMenu.hpp"


static CGravSprite* gSprite;


const CSprite* createSprite(int index, const CTeam& team) {
    gSprite = CShipMenuCursorSprite::CreateSprite(index, team);
    return gSprite->GetSprite();
}


CShipMenuCursor::CShipMenuCursor(CMenu &menu, int index, const CTeam& team,
                                 const CVersusMenu& versus,
                                 std::vector<std::string>& shipTypes):
    CMenuCursor(menu, createSprite(index, team)),
    mIndex(index),
    mVersus(versus),
    mShipTypes(shipTypes),
    mInfo(index, team, versus) {

    mGravSprite.reset(gSprite);
}


void CShipMenuCursor::DrawSprite(CCanvas &canvas) {
    int x = mMenu.GetSubMenuX(mCol.ToInt()) - mSprite->GetWidth() / 2;
    int y = mMenu.GetSubMenuY(mRow.ToInt()) - mSprite->GetHeight() / 2;
    mSprite->Draw(canvas, x, y);
    CMenu &menu = GetSubMenu();
    CShipMenuItem *item = (CShipMenuItem*)&menu;
    mInfo.Draw(canvas, *item);
}


void CShipMenuCursor::OnSelect() {
    CMenu &menu = GetSubMenu();
    CShipMenuItem *item = (CShipMenuItem*)&menu;
    int nbShips = mVersus.GetMeleeType() == "Squad" ? 1 : mVersus.GetNbShips();
    std::string name = item->GetShipName();
    for(int i = 0; i < nbShips; i++) mShipTypes.push_back(name);
}
