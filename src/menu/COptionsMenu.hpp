#ifndef COPTIONSMENU_H
#define COPTIONSMENU_H


class CSprite;
class CVideoMenu;
class CControlsMenu;
class CVersusMenu;
class CClientOptions;
class CPilotInputOptions;
class CSoundMenu;
#include "CPilotOptions.hpp"
#include "CStringMenu.hpp"
#include "CMenuCursor.hpp"


typedef std::vector<std::string> ships_t;


class COptionsMenu: public CStringMenu {

public:

  COptionsMenu(CSprite *cursorSprite, const CVersusMenu& versus,
	       const CClientOptions& options);

  CClientOptions GetClientOptions(int nbPilots) const;
  void           Save() const;


private:

  CMenuCursor mCursor;
  const CVersusMenu& mVersus;
  CControlsMenu* mControlsMenu;
  CVideoMenu*    mVideoMenu;
  CSoundMenu*    mSoundMenu;

  CPilotInputOptions         GetPilotInputOptions(int i) const;
  std::vector<CPilotOptions> GetPilotOptions(int nbPilots) const;


};


#endif
