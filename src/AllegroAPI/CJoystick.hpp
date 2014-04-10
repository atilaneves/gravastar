#ifndef CJOYSTICK_H
#define CJOYSTICK_H


#include <allegro.h>


class CJoystick {

public:

  static  int  GetNbJoysticks();
  static  bool IsPressedAny(int joyNb=0);
  static  bool JoyPressed(int b,int joyNb=0);
  static  bool JoyUp(int joyNb=0);
  static  bool JoyDown(int joyNb=0);
  static  bool JoyLeft(int joyNb=0);
  static  bool JoyRight(int joyNb=0);
  virtual bool MenuCancel() { return JoyPressed(1); }
  virtual bool MenuSelect() { return JoyPressed(0);   }

};


#endif
