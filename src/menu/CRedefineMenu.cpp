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


CRedefineMenu::CRedefineMenu(const CVersusMenu &versus, int pilotNb,
			     const CPilotInputOptions &options):
  CMenu(new CRedefineIcon(*this, versus, pilotNb)),
  mCursor(*this), mIndex(pilotNb) {

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
    mCursor.SetRow(2); //skip left & right for 

  CKeyboard::Clear(); //fresh start for below

  while(true) {
    int y = mCursor.GetRow();
    if(mButtons[CPilotInput::GetName(y)]->GetType() == "Keyboard")
      mButtons[CPilotInput::GetName(y)]->SetButton(ReadScan(rootMenu));
    else //joystick it is then
      mButtons[CPilotInput::GetName(y)]->SetButton(ReadNextButton(rootMenu,
								  mIndex));
    CKeyboard::Clear();
    rootMenu.AfterMenu();
    if(mCursor.GetRow() == mCursor.GetNbRows()) break;
    mCursor.SetRow(mCursor.GetRow() + 1); //next button
  }
}


int CRedefineMenu::ReadScan(CRootMenu &rootMenu) {
 while(CKeyboard::KeyPressedAny()) RunStep(rootMenu);
 while(true) {
   for(int i=1; i<KEY_MAX; i++)
     if(key[i]) return i;
   RunStep(rootMenu);
 }
}


int CRedefineMenu::ReadNextButton(CRootMenu &rootMenu, int joyNb) { 
  while(CJoystick::IsPressedAny()) RunStep(rootMenu);
  while(true) { 
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
