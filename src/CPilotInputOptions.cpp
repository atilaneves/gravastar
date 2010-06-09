#include "CPilotInputOptions.hpp"
#include "CRedefineMenu.hpp"
#include "CDefineButtonMenu.hpp"
#include "CCycleStringEnter.hpp"
#include <allegro.h>
#include <assert.h>



int CPilotInputOptions::GetControl(const std::string& which) const {
       if(which == "Left")    return Left();
  else if(which == "Right")   return Right();
  else if(which == "Thrust")  return Thrust();
  else if(which == "Weapon")  return Weapon();
  else if(which == "Special") return Special();
  else if(which == "Super")   return Super();
  else if(which == "Start")   return Start();
  assert(0); //should never get here
  return false;
}


CPilotInputOptions::CPilotInputOptions(CCycleStringEnter &typeMenu,
				       CRedefineMenu &menu, int index):
  mType(typeMenu.GetString()),
  mLeft(menu.GetButton("Left").GetButton()),
  mRight(menu.GetButton("Right").GetButton()),
  mThrust(menu.GetButton("Thrust").GetButton()),
  mWeapon(menu.GetButton("Weapon").GetButton()),
  mSpecial(menu.GetButton("Special").GetButton()),
  mSuper(menu.GetButton("Super").GetButton()),
  mStart(menu.GetButton("Start").GetButton()),
  mIndex(index) {

}
