#include "CJoystick.hpp"


bool CJoystick::IsPressedAny(int joyNb) {
  poll_joystick();
  for(int buttonNb=0; buttonNb<joy[joyNb].num_buttons; buttonNb++)
    if(joy[joyNb].button[buttonNb].b) return true;
  return false; //default, nth was pressed
}


bool CJoystick::JoyPressed(int buttonNb,int joyNb) {
  if(GetNbJoysticks() > 0) { 
    poll_joystick();
    return joy[joyNb].button[buttonNb].b;
  }
  else return false;
}


bool CJoystick::JoyLeft(int joyNb) {
  if(GetNbJoysticks() > 0) { 
    poll_joystick();
    return joy[joyNb].stick[0].axis[0].d1; 
  } 
  else return false;
}


bool CJoystick::JoyRight(int joyNb) {
  if(GetNbJoysticks() > 0) { 
    poll_joystick();
    return joy[joyNb].stick[0].axis[0].d2; 
  } 
  else return false;
}


bool CJoystick::JoyUp(int joyNb) {
  if(GetNbJoysticks() > 0) { 
    poll_joystick();
    return joy[joyNb].stick[0].axis[1].d1; 
  } 
  else return false;
}


bool CJoystick::JoyDown(int joyNb) {
  if(GetNbJoysticks() > 0) { 
    poll_joystick();
    return joy[joyNb].stick[0].axis[1].d2; 
  } 
  else return false;
}


int CJoystick::GetNbJoysticks() {
  return num_joysticks;
}
