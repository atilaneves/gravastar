#ifndef CKEYBOARD_H
#define CKEYBOARD_H


#include <allegro.h>


class CKeyboard {

public:

  enum { kEsc=KEY_ESC, kEnter=KEY_ENTER,
         kY=KEY_Y, kN=KEY_N, kUp=KEY_UP, kDown=KEY_DOWN,
         kLeft=KEY_LEFT, kRight=KEY_RIGHT };

  static  void Clear();
  static  bool KeyPressed();
  static  bool KeyPressed(int keyNb);
  static  bool KeyPressedAny();
  static  int  ReadKey();
  static  int  ReadScan();
  static  int  ScanToASCII(int s);


};


#endif
