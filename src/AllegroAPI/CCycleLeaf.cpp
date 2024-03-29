#include "CCycleLeaf.hpp"
#include "CFont.hpp"
#include "CMenuIconCycle.hpp"
#include <stdio.h>


static CMenuIconCycle *gIconCycle;

CCycleLeaf::CCycleLeaf(const std::string& title, int max, int min):
   CMenu(gIconCycle = new CMenuIconCycle(title, *this)),
   mCycle(max, min),
   mTitle(title),
   mIconCycle(gIconCycle) {
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
