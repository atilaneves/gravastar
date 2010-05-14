#ifndef CSTRINGMENU_H
#define CSTRINGMENU_H


class CMenuCursor;
class CMenuIcon;
class CFont;
#include "CMenu.hpp"
#include <string>



class CStringMenu: public CMenu {

public:

  CStringMenu(const std::string &title);
  virtual ~CStringMenu() { }

  static const CFont& GetFont() { return *sFont; }
  const std::string&  GetTitle() const;
  static       void   SetFont(const CFont *font);


private:

  static const CFont *sFont;


};

#endif
