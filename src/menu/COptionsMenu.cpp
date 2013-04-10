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

CClientOptions COptionsMenu::GetClientOptions(int nbPilots) const {
    return CClientOptions(mVersus.GetPilotOptions(nbPilots,
                                                  mControlsMenu->GetPilotInputOptions(nbPilots)),
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
