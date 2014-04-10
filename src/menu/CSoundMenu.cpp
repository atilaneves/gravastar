#include "CSoundMenu.hpp"
#include "CCycleLeaf.hpp"
#include "CMeleeOptions.hpp"
#include "CSound.hpp"
#include "CSoundMP3.hpp"
#include "CClientOptions.hpp"


CSoundMenu::CSoundMenu(CSprite *cursorSprite, const CClientOptions& options):
  CStringMenu("Audio"),
  mCursor(*this, cursorSprite) {

  AddMenu(mSoundVolume = new CCycleLeaf("Sound FX Volume: ", 10, 0));
  AddMenu(mMusicVolume = new CCycleLeaf("Music Volume: ", 10, 0));
  mSoundVolume->SetCycle(options.GetSoundVolume());
  mMusicVolume->SetCycle(options.GetMusicVolume());

  SetVolumes();
}


void CSoundMenu::Update(CRootMenu &rootMenu) {
  SetVolumes();
}


void CSoundMenu::SetVolumes() {
 CSound::SetMasterVolume(mSoundVolume->GetCycle() / 10.0);
 CSoundMP3::SetMasterVolume(mMusicVolume->GetCycle() / 10.0);
}


int CSoundMenu::GetSoundVolume() const {
  return mSoundVolume->GetCycle();
}


int CSoundMenu::GetMusicVolume() const {
  return mMusicVolume->GetCycle();
}
