#ifndef CGRAVSCREEN_H
#define CGRAVSCREEN_H


#include "CCanvas.hpp"
#include "COneSplitScreen.hpp"
#include "CTwoSplitScreens.hpp"
#include "CFourSplitScreens.hpp"
#include "CTimeCounter.hpp"
#include "CFont.hpp"
#include "CScreenPos.hpp"
#include <vector>


class CClientOptions;
class CPilot;
class CSong;


class CGravScreen {

public:

  CGravScreen(const CCanvas &levelCanvas, const CClientOptions &options,
              const CSong& song);
  ~CGravScreen();

  void     Draw(const pilots_t &pilots);
  CCanvas& GetCanvas() { return mCanvas; }


private:

  int mOldWidth, mOldHeight;
  CCanvas mCanvas;
  const CSong& mSong;
  CFont mFont;
  bool mSmartSplit;
  COneSplitScreen   mOneSplitScreen;
  CTwoSplitScreens  mTwoSplitScreens;
  CFourSplitScreens mFourSplitScreens;
  CTimeCounter mTimeCounter;

  void PrintSongTitle();
  CSplitScreens& GetSplitScreens(const CScreenPos& centre, int nbHumans);

};


#endif
