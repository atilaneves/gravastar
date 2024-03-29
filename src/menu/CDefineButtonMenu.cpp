#include "CDefineButtonMenu.hpp"
#include "CKeyboard.hpp"
#include "CMenuIconString.hpp"
#include "CFont.hpp"
#include <stdio.h>


CDefineButtonMenu::CDefineButtonMenu(const std::string &title,
                                     const std::string &type,
                                     int button):
  CStringMenu(title),
  mTitle(title), mType(type), mButton(button) {

}


void CDefineButtonMenu::DrawIcon(CCanvas &canvas, int x, int y,
                                 bool highlight) {
  CMenu::DrawIcon(canvas, x, y, highlight);
  const CFont& font = CStringMenu::GetFont();
  font.Print(canvas, x + 100, y,
             CMenuIconString::GetColour(highlight), -1, GetButtonName());
}


std::string CDefineButtonMenu::GetButtonName() const {
  char buttonName[200] = "";

  if(mType == "Keyboard")
    sprintf(buttonName, "%c", CKeyboard::ScanToASCII(mButton));
  else if(mTitle != "Left" && mTitle != "Right") //neither
    sprintf(buttonName, "B%d", mButton + 1);

  return buttonName;
}
