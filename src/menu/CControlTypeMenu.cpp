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

  if(options.Type() == "Joystick") SetCycle(1);

}



void CControlTypeMenu::Run(CRootMenu &rootMenu) {
  CCycleStringEnter::Run(rootMenu);
  mRedefine.SetControlType(GetString());
  mRedefine.Run(rootMenu);
}
