#include "CMenuInputKey.hpp"
#include "CKeyboard.hpp"


CMenuInputKey CMenuInputKey::sUp(CKeyboard::kUp);
CMenuInputKey CMenuInputKey::sDown(CKeyboard::kDown);
CMenuInputKey CMenuInputKey::sLeft(CKeyboard::kLeft);
CMenuInputKey CMenuInputKey::sRight(CKeyboard::kRight);
CMenuInputKey CMenuInputKey::sSelect(CKeyboard::kEnter);
CMenuInputKey CMenuInputKey::sCancel(CKeyboard::kEsc);


CMenuInputKey::CMenuInputKey(int key):
  mKey(key), mWasPressing(false) {

}


bool CMenuInputKey::Pressed() {

  bool pressed = CKeyboard::KeyPressed(mKey);

 if(pressed && !mWasPressing) {
    mWasPressing=true;
    return true;
 }
 if(!pressed)
    mWasPressing=false;

 return false;
}
