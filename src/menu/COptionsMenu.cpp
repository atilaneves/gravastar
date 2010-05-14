#include "COptionsMenu.hpp"
#include "CVideoMenu.hpp"
#include "CSoundMenu.hpp"
#include "CControlsMenu.hpp"
#include "CVersusMenu.hpp"
#include "CClientOptions.hpp"



COptionsMenu::COptionsMenu(CSprite *cursorSprite,
			   const CVersusMenu &versus,
			   const CClientOptions& options):
  CStringMenu("Options"),
  mCursor(*this, cursorSprite),
  mVersus(versus) {

  AddMenu(mControlsMenu = new CControlsMenu(versus, options));
  AddMenu(mVideoMenu    = new CVideoMenu(cursorSprite, options));
  AddMenu(mSoundMenu    = new CSoundMenu(cursorSprite, options));
}


CPilotInputOptions COptionsMenu::GetPilotInputOptions(int i) const {
  return mControlsMenu->GetPilotInputOptions(i);
}


std::vector<CPilotOptions> COptionsMenu::GetPilotOptions(int nbPilots) const {

  std::vector<CPilotOptions> pilots;    

  for(int i = 0; i < nbPilots; ++i)
    pilots.push_back(CPilotOptions(mVersus.GetPilotName(i),
				   mVersus.GetPilotType(i),
				   mVersus.GetPilotTeam(i),
				   mVersus.GetShipTypes(i),
				   GetPilotInputOptions(i)));

  return pilots;
}


CClientOptions COptionsMenu::GetClientOptions(int nbPilots) const {
  return CClientOptions(GetPilotOptions(nbPilots),
			mVideoMenu->GetWindowed(),
			mVideoMenu->GetWidth(), mVideoMenu->GetHeight(),
			mSoundMenu->GetSoundVolume(),
			mSoundMenu->GetMusicVolume(),
			mVideoMenu->GetSmartSplit());
}


void COptionsMenu::Save() const {
  const int kMaxNbPilots = 4;
  GetClientOptions(kMaxNbPilots).Save();
}

