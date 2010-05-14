#include "CSpriteFinder.hpp"
#include "CCanvas.hpp"
#include "CColour.hpp"


Positions_t CSpriteFinder::FindSprites(const CCanvas &haystack,
				       const CCanvas &needle) {

  Positions_t positions;
  
  for(int y = 0; y < haystack.GetHeight() - needle.GetHeight() + 1; y++)
    for(int x = 0; x < haystack.GetWidth() - needle.GetWidth() + 1; x++)
      if(IsSpriteHere(haystack, needle, x, y))
	positions.push_back(CScreenPos(x, y));
  
  return positions;
}


bool CSpriteFinder::IsSpriteHere(const CCanvas &haystack, const CCanvas &needle,
				 int x0, int y0) {

  for(int x = x0; x < x0+needle.GetWidth(); x++)
    for(int y = y0; y < y0+needle.GetHeight(); y++)
      if(needle.GetPixel(x-x0, y-y0) != CColour::GetBlack() &&
	 haystack.GetPixel(x, y) != needle.GetPixel(x-x0, y-y0))
	  return false;

  return true;
}
