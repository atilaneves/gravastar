#include "CFontTitle.hpp"
#include "CResolution.hpp"


CFontTitle::CFontTitle(int fontIndex, int colour, const std::string &title):
  mFont(fontIndex),
  mColour(colour),
  mTitle(title) {

}


void CFontTitle::Draw(CCanvas &canvas) {
  int x   = CResolution::GetWidth()/2;
  int y   = 0;
  int bg  = -1;
  mFont.PrintCentre(canvas, x, y, mColour, bg, mTitle);
}
