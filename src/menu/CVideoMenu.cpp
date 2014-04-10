#include "CVideoMenu.hpp"
#include "CCycleString.hpp"
#include "CMeleeOptions.hpp"
#include "CResolution.hpp"
#include "CClientOptions.hpp"
#include "CRootMenu.hpp"


CVideoMenu::CVideoMenu(CSprite *cursorSprite, const CClientOptions& options):
  CStringMenu("Video"),
  mCursor(*this, cursorSprite) {

  const std::string rnames[] = {"640x480", "800x600", "1024x640", "1024x768",
				"1280x720", "1280x768", "1280x800"};
  int size = sizeof(rnames) / sizeof(std::string);
  strings_t rNames(rnames, rnames + size);
  AddMenu(mResolution = new CCycleString("Resolution: ", rNames, size - 1, 0));

  const std::string wnames[] = { "Full Screen", "Windowed" };
  size = sizeof(wnames) / sizeof(std::string);
  strings_t wNames(wnames, wnames + size);
  AddMenu(mWindowed=new CCycleString("Graphics Mode: ", wNames, size - 1, 0));
  const std::string snames[] = { "On", "Off" };
  size = sizeof(snames) / sizeof(std::string);
  strings_t sNames(snames, snames + size);
  AddMenu(mSmart=new CCycleString("Smart Split Screen: ", sNames, size-1, 0));

  int mode = 0;
  do {
    mResolution->SetCycle(mode);
    ++mode;
  } while(GetWidth() != options.GetWidth() ||
	  GetHeight() != options.GetHeight());

  mWindowed->SetCycle(options.IsWindowed());

  mOldResolution = mResolution->GetCycle();
  mOldWindowed   = mWindowed->GetCycle();
}


void CVideoMenu::Run(CRootMenu &rootMenu) {
  CMenu::Run(rootMenu);

  if(mResolution->GetCycle() != mOldResolution) {
    rootMenu.NewCanvas(GetWidth(), GetHeight());
    CResolution::SetMode(GetWidth(), GetHeight());
  }

  mOldResolution = mResolution->GetCycle();
}


void CVideoMenu::Update(CRootMenu &rootMenu) {

  if(mWindowed->GetCycle()   != mOldWindowed) {
    rootMenu.NewCanvas(GetWidth(), GetHeight());
    bool windowed = mWindowed->GetCycle() == 1 ? true : false;
    CResolution::SetWindowed(windowed);
    CResolution::SetMode(GetWidth(), GetHeight());
    mOldResolution = mResolution->GetCycle();
  }

  mOldWindowed = mWindowed->GetCycle();
}


int CVideoMenu::GetWidth() const {
  static const int modeWidths[] = { 640, 800, 1024, 1024, 1280, 1280, 1280 };
  return modeWidths[mResolution->GetCycle()];
}


int CVideoMenu::GetHeight() const {
  static const int modeHeights[] = { 480, 600, 640, 768, 720, 768, 800 };
  return modeHeights[mResolution->GetCycle()];
}


bool CVideoMenu::GetWindowed() const {
  return mWindowed->GetCycle() == 0;
}


bool CVideoMenu::GetSmartSplit() const {
  return mSmart->GetCycle() == 0;
}
