#ifndef CSPRITEFINDER_H
#define CSPRITEFINDER_H


#include "CScreenPos.hpp"
#include <vector>
class CCanvas;


typedef std::vector<CScreenPos> Positions_t;


class CSpriteFinder {

public:

  static Positions_t FindSprites(const CCanvas &haystack,
				 const CCanvas &needle);

  static bool IsSpriteHere(const CCanvas &haystack, const CCanvas &needle,
			   int x0, int y0);


private:


};


#endif
