#ifndef CFONTTITLE_H
#define CFONTTITLE_H


#include "CMenuBackground.hpp"
#include "CFont.hpp"
#include <string>


class CFontTitle:public CMenuBackground {

public:

  CFontTitle(int fontIndex, int colour, const std::string &title);
  virtual ~CFontTitle() { }

  virtual void Draw(CCanvas &canvas) override;
  virtual void NewCanvas(int width, int height) override {}

private:

  CFont       mFont;
  int         mColour;
  std::string mTitle;

};

#endif
