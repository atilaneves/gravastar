#include "CControlTypeMenu.hpp"
#include "CRedefineMenu.hpp"
#include "CPilotInputOptions.hpp"


CControlTypeMenu::CControlTypeMenu(CRedefineMenu &redefine,
				   const CPilotInputOptions& options,
				   const std::string &title,
				   const strings_t& strings,
				   int max, int min):
  CCycleStringEnter(title, strings, max, min),
  mRedefine(redefine) {

  //set the menu to "Joystick" as well by going to index 1
  if(options.Type() == "Joystick") SetCycle(1);

}



void CControlTypeMenu::Run(CRootMenu &rootMenu) {
  CCycleStringEnter::Run(rootMenu);
  mRedefine.SetControlType(GetString());
  mRedefine.Run(rootMenu); //run now since joy and key buttons are incomp.
}
