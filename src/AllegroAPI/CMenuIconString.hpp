#ifndef CMENU_ICON_STRING_H
#define CMENU_ICON_STRING_H


class CFont;
#include "CMenuIcon.hpp"
#include "CColour.hpp"
#include <string>


class CMenuIconString:public CMenuIcon {

public:
  
  CMenuIconString(const std::string &title, const CFont &font);
  virtual ~CMenuIconString() { }
  
  virtual void Draw(CCanvas &canvas, int x, int y, bool highlight=false);
  virtual int  GetHeight() const;
  static  int  GetColour(bool h) { return  h ? GetMenuHi() : GetMenuLo(); }
  static  int  GetMenuHi() { return CColour::GetColour(255, 255, 255); }
  static  int  GetMenuLo() { return CColour::GetColour(140, 140, 140); }
  const std::string& GetTitle() const { return mTitle; }
  virtual int  GetWidth()  const;
          void SetTitle(const std::string& t) { mTitle = t; }

  
  
private:

  std::string  mTitle;
  const CFont& mFont;
  
};

#endif
