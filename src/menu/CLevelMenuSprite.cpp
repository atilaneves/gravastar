#include "CLevelMenuSprite.hpp"
#include "CSprite.hpp"
#include "CCanvas.hpp"
#include "CLevelHeader.hpp"
#include "CCanvas.hpp"
#include "CColour.hpp"
#include <stdio.h>


CLevelMenuSprite::CLevelMenuSprite(int levelNb) {

 CLevelHeader levelHeader(levelNb);
 mTitle        = levelHeader.GetTitle();
 mWidthString  = GetWidthDim(levelHeader.GetWidth());
 mHeightString = GetHeightDim(levelHeader.GetHeight());

 int stretchW = GetStretchWidth(levelHeader.GetCanvas());
 int stretchH = GetStretchHeight(levelHeader.GetCanvas());
 CCanvas canvas(stretchW, stretchH);
 const int x = 0, y = 0;
 levelHeader.GetCanvas().StretchBlit(canvas, x, y, stretchW, stretchH);

 for(int y = 0; y < canvas.GetHeight(); y++)
   for(int x = 0; x < canvas.GetWidth(); x++)
     if(canvas.GetPixel(x, y) == CColour::GetBlack())
       canvas.PutPixel(x, y, canvas.GetMask());

 mSprite.reset(new CSprite(canvas.GetData()));
}


int CLevelMenuSprite::GetStretchWidth(CCanvas &canvas) const {
 return canvas.GetWidth() > canvas.GetHeight() ? kWidth : kHeight;
}


int CLevelMenuSprite::GetStretchHeight(CCanvas &canvas) const {
 return canvas.GetWidth() > canvas.GetHeight() ? kHeight : kWidth;
}


std::string CLevelMenuSprite::GetDim(const std::string &name, int dim) {
  char dimString[100];
  sprintf(dimString, ": %d", dim);

  if(mTitle == "Random") //regular level
    return name + ": ???";
  else
    return name + dimString;
}


void CLevelMenuSprite::Draw(CCanvas &canvas, int x, int y)  const {
 mSprite->Draw(canvas,x,y);
}


int CLevelMenuSprite::GetWidth() const {
 return mSprite->GetWidth();
}


int CLevelMenuSprite::GetHeight() const {
 return mSprite->GetHeight();
}
