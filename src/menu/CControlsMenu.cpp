#include "CControlsMenu.hpp"
#include "CResolution.hpp"
#include "CControlTypeMenu.hpp"
#include "CRedefineMenu.hpp"
#include "CPilotInputOptions.hpp"
#include "CClientOptions.hpp"
#include "CResolution.hpp"
#include "CMenuIconString.hpp"
#include "CFont.hpp"


CControlsMenu::CControlsMenu(const CVersusMenu &versus,
			     const CClientOptions &options):
  CStringMenu("Controls"),
  mCursor(*this),
  mVersus(versus) {

  const char *ctrlNames[] = { "Keyboard", "Joystick" };
  strings_t titles(ctrlNames, ctrlNames + sizeof(ctrlNames) / sizeof(char*));
  for(int i = 0; i < kMaxNbPilots; i++) {
    const CPilotInputOptions &op=options.GetPilotOptions(i).GetInputOptions();
    mRedefines.push_back(new CRedefineMenu(versus, i, *this, op));
    mControlTypes.push_back(new CControlTypeMenu(*mRedefines[i], op, "",
						 titles, 1, 0));
    AddMenu(mControlTypes[i], i);
    AddMenu(mRedefines[i], i);
  }
}

  

int CControlsMenu::GetSubMenuX(int column) const {
  return CMenu::GetSubMenuX(column) + CResolution::GetWidth() / 35;
}


CPilotInputOptions CControlsMenu::GetPilotInputOptions(int i) {
  return CPilotInputOptions(*mControlTypes[i], *mRedefines[i],
			    GetJoyIndex(i));
}


int CControlsMenu::GetJoyIndex(int i) const {
  int joyIndex = -1;
  for(int j = 0; j <= i; j++)
    if(mControlTypes[j]->GetString() == "Joystick")
      joyIndex++;
  return joyIndex;
}


void CControlsMenu::Draw(CCanvas &canvas) {
  CMenu::Draw(canvas);
  std::string str1 = "If the start and super buttons are the same ";
  str1 += "the super is ";
  std::string str2 = "performed by pressing weapon and ";
  str2 += "special at the same time";
  CStringMenu::GetFont().Print(canvas, CResolution::GetWidth() / 8,
			       (CResolution::GetHeight()*17)/20,
			       CMenuIconString::GetMenuHi(), -1, str1);
  
  CStringMenu::GetFont().Print(canvas, CResolution::GetWidth() / 8,
			       (CResolution::GetHeight()*17)/20 + 15,
			       CMenuIconString::GetMenuHi(), -1, str2);
}
