#include "CGravScreen.hpp"
#include "CClientOptions.hpp"
#include "CPilot.hpp"
#include "CResolution.hpp"
#include "CSong.hpp"
#include "CColour.hpp"
#include "fontsdat.h"


CGravScreen::CGravScreen(const CCanvas &levelCanvas,
			 const CClientOptions &options,
			 const CSong& song):
  mOldWidth(CResolution::GetWidth()), mOldHeight(CResolution::GetHeight()),
  mCanvas(options.GetWidth(), options.GetHeight()),
  mSong(song), mFont(EmpireBuilderDocument9),
  mSmartSplit(options.IsSmartSplit()),
  mOneSplitScreen(levelCanvas, mCanvas),
  mTwoSplitScreens(levelCanvas, mCanvas),
  mFourSplitScreens(levelCanvas, mCanvas) {

  CResolution::SetMode(options.GetWidth(), options.GetHeight());
  mTimeCounter.Start(4);
}



CGravScreen::~CGravScreen() {
  CResolution::SetMode(mOldWidth, mOldHeight);
}


void CGravScreen::Draw(const pilots_t &pilots) {
  mCanvas.Clear();
  pilots_t humans = mOneSplitScreen.GetHumans(pilots);
  CScreenPos pos = mOneSplitScreen.GetCentre(humans);
  CSplitScreens* screens;

  if(pos.GetX() >= 0 && mSmartSplit) screens = &mOneSplitScreen;
  else if(humans.size() == 2)        screens = &mTwoSplitScreens;
  else                               screens = &mFourSplitScreens;

  screens->Grab(humans);
  screens->DrawRadar(pilots);
  PrintSongTitle();
  mCanvas.Flip();
}


void CGravScreen::PrintSongTitle() {
  if(!mTimeCounter.IsActive()) return;
  int x = CResolution::GetWidth() / 2;
  int y = (CResolution::GetHeight() * 17) / 20;
  mFont.PrintCentre(mCanvas, x, y, CColour::GetWhite(), -1, mSong.GetName());
}
