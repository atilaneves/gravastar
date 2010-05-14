#ifndef C_LEVELMENU_SPRITE_H
#define C_LEVELMENU_SPRITE_H


class CSprite;
class CCanvas;
#include "CSprite.hpp"
#include <string>
#include <memory>


class CLevelMenuSprite {

public:

 CLevelMenuSprite(int levelNb);

 void               Draw(CCanvas &canvas, int x, int y) const;
 int                GetHeight() const;
 const std::string& GetHeightString() const { return mHeightString; }
 const std::string& GetTitle() const        { return mTitle; }
 int                GetWidth() const;
 const std::string& GetWidthString() const { return mWidthString; }



private:

  enum { kWidth = 400, kHeight = 250 };

  std::string mTitle;
  std::string mWidthString;
  std::string mHeightString;
  std::auto_ptr<CSprite> mSprite;
  
  std::string GetDim(const std::string& name, int dim);
  std::string GetHeightDim(int h)  { return GetDim("Height", h); }
  int         GetStretchHeight(CCanvas &canvas) const;
  int         GetStretchWidth(CCanvas &canvas)  const;
  std::string GetWidthDim(int w)   { return GetDim("Width", w); }

 

};



#endif
