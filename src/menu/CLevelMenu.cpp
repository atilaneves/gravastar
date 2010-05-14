#include "CLevelMenu.hpp"
#include "CResolution.hpp"
#include "CFont.hpp"
#include "CMenuIconString.hpp"
#include "CRect.hpp"
#include "CColour.hpp"
#include "CLevelMenuSprite.hpp"
#include "CCanvas.hpp"
#include "CMeleeStart.hpp"
#include "CGravOptions.hpp"



CLevelMenu::CLevelMenu(const CGravMenu &gravMenu):
  CStringMenu("Select Level"),
  mCursor(*this), mSound("selectLevel") {

  strings_t titles;
  for(int i = 0; i <= mLevelCounter.GetNbLevels(); i++) {
    mSprites.push_back(new CLevelMenuSprite(i));
    titles.push_back(mSprites[i]->GetTitle());
  }

  AddMenu(mMeleeStart = new CMeleeStart(gravMenu, titles));
  mMeleeStart->SetCycle(0);
}


CLevelMenu::~CLevelMenu() {
  for(unsigned int i = 0; i < mSprites.size(); i++)
    delete mSprites[i];
}


void CLevelMenu::Draw(CCanvas &canvas) {
  CMenu::Draw(canvas);
  const int x = int(0.9 * CResolution::GetWidth()) - GetSprite().GetWidth();
  const int y = int(0.15 * CResolution::GetHeight());
  GetSprite().Draw(canvas, x, y);
  const CFont& font = CStringMenu::GetFont();
  font.Print(canvas, GetSubMenuX(0), GetSubMenuY(2),
	     CMenuIconString::GetMenuLo(), -1,
	     GetSprite().GetWidthString());
  font.Print(canvas, GetSubMenuX(0), GetSubMenuY(3),
	     CMenuIconString::GetMenuLo(), -1,
	     GetSprite().GetHeightString());
  CRect r(canvas, x - 1, y - 1,
	  x + GetSprite().GetWidth(), y + GetSprite().GetHeight(),
	  CColour::GetWhite());

}


const CLevelMenuSprite& CLevelMenu::GetSprite() const {
  return *mSprites[mMeleeStart->GetCycle()];
}


int CLevelMenu::GetSubMenuX(int column) const {
 return CResolution::GetWidth() / 10;
}


int CLevelMenu::GetSubMenuY(int row) const {
 return CMenu::GetSubMenuY(row) - CResolution::GetHeight() / 16;
}


int CLevelMenu::GetLevelNb() const {
  return mMeleeStart->GetCycle() ? mMeleeStart->GetCycle() :
    mLevelCounter.GetRandomLevel();
}


void CLevelMenu::Run(CRootMenu &rootMenu) {
  mSound.PlayCentre();
  CMenu::Run(rootMenu);
}
