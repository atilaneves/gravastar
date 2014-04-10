#ifndef CMENU_SOUND_H
#define CMENU_SOUND_H


#include "CStringMenu.hpp"
#include "CMenuCursor.hpp"
class CSprite;
class CCycleLeaf;
class CClientOptions;


class CSoundMenu: public CStringMenu {

public:

  CSoundMenu(CSprite *cursorSprite, const CClientOptions& options);

  int GetSoundVolume() const;
  int GetMusicVolume() const;


private:

  CMenuCursor mCursor;
  CCycleLeaf *mSoundVolume, *mMusicVolume;
  
  virtual void Update(CRootMenu &rootMenu);
          void SetVolumes();

};

#endif
