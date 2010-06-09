#ifndef CREDEFINE_MENU_H
#define CREDEFINE_MENU_H


#include "CMenu.hpp"
#include "CMenuCursor.hpp"
#include <map>
#include <string>
class CVersusMenu;
class CDefineButtonMenu;
class CPilotInputOptions;
class CMenuInputRedefine;
class CControlsMenu;


class CRedefineMenu: public CMenu {

public:

  CRedefineMenu(const CVersusMenu &versus, int pilotNb,
		const CControlsMenu& controlsMenu,
		const CPilotInputOptions& options);
  virtual ~CRedefineMenu() { }

  virtual void Run(CRootMenu &rootMenu);

  CDefineButtonMenu& GetButton(const std::string& s)  {
    return *mButtons[s]; }
  int                GetIndex() const { return mIndex; }
  int                GetNbButtons()   const { return mButtons.size(); }
  void               SetControlType(const std::string &type);


private:

  CMenuInputRedefine* mMenuInputRedefine;
  CMenuCursor mCursor;
  int mIndex;
  const CControlsMenu &mControlsMenu;
  std::map<std::string, CDefineButtonMenu*> mButtons;

  int ReadNextButton(CRootMenu &rootMenu, int joyNb);
  int ReadScan(CRootMenu &rootMenu);


};

#endif
