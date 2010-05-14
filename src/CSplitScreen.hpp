#ifndef CSPLITSCREEN_H
#define CSPLITSCREEN_H

//implements a split screen, shows a window of a larger canvas


#include "CSubCanvas.hpp"
#include "CSubDisplay.hpp"
#include "CScreenPos.hpp"
#include "CVector2.hpp"
#include "CRadar.hpp"
#include <vector>
class CPilot;


class CSplitScreen: public CSubDisplay {

public:

  enum { kSplitBorder=20 };

  CSplitScreen(const CCanvas &levelCanvas, CCanvas &drawCanvas,
	       int width, int height,
	       int drawX, int drawY);
  CSplitScreen(const CSplitScreen &split);

  void       DrawRadar(const pilots_t& pilots, const pilots_t& humans);
  CScreenPos GetCentre(const pilots_t& pilots);
  pilots_t   GetHumans(const pilots_t& pilots);
  void       Grab(const pilots_t& pilots);


private:

  CSubCanvas     mSubCanvas;
  const CCanvas* mLevelCanvas;
  CRadar         mRadar;

  CScreenPos GetGrabPos(const pilots_t& pilots);
  int        GetRealGrabPos(int pos, int subLength, int levelLength);

};


#endif
