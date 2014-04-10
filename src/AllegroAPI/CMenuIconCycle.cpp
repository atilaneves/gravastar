#include "CMenuIconCycle.hpp"
#include "CFont.hpp"
#include "CCanvas.hpp"
#include "CStringMenu.hpp"
#include "CCycleLeaf.hpp"



CMenuIconCycle::CMenuIconCycle(const std::string &title,
                               const CCycleLeaf &cycleMenu):
    mFont(CStringMenu::GetFont()), mTitle(title, mFont), mCycleMenu(cycleMenu) {

}


void CMenuIconCycle::Draw(CCanvas &canvas, int x, int y, bool highlight) const {
    mTitle.Draw(canvas, x, y, highlight);
    mFont.Print(canvas, x + mTitle.GetWidth() + 10, y,
                CMenuIconString::GetColour(highlight), -1,
                mCycleMenu.GetString());
}


int CMenuIconCycle::GetWidth() const {
    return mTitle.GetWidth() + mFont.GetLength(mCycleMenu.GetString().c_str());
}
