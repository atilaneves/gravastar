#include "CCycleLeaf.hpp"
#include "CFont.hpp"
#include "CMenuIconCycle.hpp"
#include <stdio.h>


CCycleLeaf::CCycleLeaf(const std::string& title, int max, int min):
   CMenu(nullptr),
   mCycle(max, min),
   mTitle(title),
   mIconCycle(nullptr) {
  mIconCycle = new CMenuIconCycle(title, *this);
  AdoptIcon(mIconCycle);
}


void CCycleLeaf::LeafAction(int delta) {
  mCycle += delta;
}


std::string CCycleLeaf::GetString() const {
  char str[200];
  sprintf(str, "%d", mCycle.ToInt());
  return str;
}


void CCycleLeaf::SetIconTitle(const std::string& title) {
  mIconCycle->SetTitle(title);
}
