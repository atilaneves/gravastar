#ifndef CDEFINEBUTTONMENU_H
#define CDEFINEBUTTONMENU_H


#include "CStringMenu.hpp"


class CDefineButtonMenu: public CStringMenu {

public:

  CDefineButtonMenu(const std::string &title, const std::string &type,
		    int button);

  void        DrawIcon(CCanvas &canvas, int x, int y, bool highlight);
  int         GetButton() const { return mButton; }
  std::string GetButtonName() const;
  std::string GetType() const { return mType; }
  void        SetButton(int b) { mButton = b; }
  void        SetType(const std::string& t) { mType = t; }


private:

  std::string mTitle, mType;
  int mButton;


};


#endif
