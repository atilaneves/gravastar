#include "CMenuIconString.hpp"
#include "CFont.hpp"
#include "CCanvas.hpp"



CMenuIconString::CMenuIconString(const std::string &title, const CFont &font):
   mTitle(title), mFont(font){

}


void CMenuIconString::Draw(CCanvas &canvas, int x, int y, bool highlight) const {
  mFont.Print(canvas, x, y, GetColour(highlight), -1, mTitle.c_str());
}


int CMenuIconString::GetHeight() const {
  return mFont.GetHeight();
}


int CMenuIconString::GetWidth() const {
  return mFont.GetLength(mTitle.c_str());
}
