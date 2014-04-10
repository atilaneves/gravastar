#include "CRedefineMenu.hpp"
#include "CKeyboard.hpp"
#include "CJoystick.hpp"
#include "CCycleString.hpp"
#include "CPilotInputOptions.hpp"
#include "CRedefineIcon.hpp"
#include "CDefineButtonMenu.hpp"
#include "CPilotInput.hpp"
#include "CRootMenu.hpp"
#include "CPilotInputOptions.hpp"
#include "CMenuInputRedefine.hpp"
#include "CControlsMenu.hpp"


CRedefineMenu::CRedefineMenu(const CVersusMenu &versus, int pilotNb,
			     const CControlsMenu &controlsMenu,
			     const CPilotInputOptions &options):
  CMenu(new CRedefineIcon(*this, versus, pilotNb)),
  mCursor(*this), mIndex(pilotNb), mControlsMenu(controlsMenu) {

  mMenuInputRedefine = new CMenuInputRedefine;
  mCursor.AdoptInput(mMenuInputRedefine);

  for(int i = 0; i < CPilotInput::GetNbControls(); i++) {
    const std::string& name = CPilotInput::GetName(i);
    mButtons[name] = new CDefineButtonMenu(name, options.Type(),
					   options.GetControl(name));
    AddMenu(mButtons[name]);
  }

}


void CRedefineMenu::Run(CRootMenu &rootMenu) {

  if(mButtons["Left"]->GetType() == "Keyboard")
    mCursor.SetRow(0);
  else
    mCursor.SetRow(2); //skip left & right for joystick

  CKeyboard::Clear(); //fresh start for below

  while(true && !mMenuInputRedefine->Cancel()) {
    int y = mCursor.GetRow();
    int button = mButtons[CPilotInput::GetName(y)]->GetType() == "Keyboard" ?
      ReadScan(rootMenu) :
      ReadNextButton(rootMenu, mControlsMenu.GetJoyIndex(mIndex));

    if(!mMenuInputRedefine->Cancelled())
      mButtons[CPilotInput::GetName(y)]->SetButton(button);
    else
      break;

    CKeyboard::Clear();
    rootMenu.AfterMenu();
    if(mCursor.GetRow() == mCursor.GetNbRows()) break;
    mCursor.SetRow(mCursor.GetRow() + 1); //next button
  }

  mMenuInputRedefine->Reset();
}


int CRedefineMenu::ReadScan(CRootMenu &rootMenu) {
  //1st, wait til key is no longer pressed
  while(CKeyboard::KeyPressedAny()) RunStep(rootMenu);
  CKeyboard::Clear();
  while(true) {
    if(mMenuInputRedefine->Cancel()) return 0;

    for(int i = 1; i < KEY_MAX; i++) {
      if(i == CKeyboard::kEsc)     continue;
      if(CKeyboard::KeyPressed(i)) return i;
    }

    RunStep(rootMenu);
  }
}


int CRedefineMenu::ReadNextButton(CRootMenu &rootMenu, int joyNb) {
  //1st, wait til no button is pressed
  while(CJoystick::IsPressedAny(joyNb)) RunStep(rootMenu);
  while(true) {
    if(mMenuInputRedefine->Cancel()) return 0;

    poll_joystick();
    for(int buttonNb = 0; buttonNb < joy[joyNb].num_buttons; buttonNb++)
      if(joy[joyNb].button[buttonNb].b) return buttonNb;
    RunStep(rootMenu);
  }
}


void CRedefineMenu::SetControlType(const std::string &type) {
  for(int i = 0; i < CPilotInput::GetNbControls(); i++) {
    mButtons[CPilotInput::GetName(i)]->SetType(type);
  }
}
