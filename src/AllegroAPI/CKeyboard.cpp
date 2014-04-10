#include "CKeyboard.hpp"
#include <ctype.h>


void CKeyboard::Clear() {
 clear_keybuf();
}


bool CKeyboard::KeyPressed() {
 return (bool)keypressed();
}


bool CKeyboard::KeyPressed(int keyNb) {
 return (bool)key[keyNb];
}


int CKeyboard::ReadKey() {
 return readkey();
}


int CKeyboard::ReadScan() {
  return readkey() >> 8;
}


int CKeyboard::ScanToASCII(int s) {
 return toupper(scancode_to_ascii(s));
}


bool CKeyboard::KeyPressedAny() {
 for(int i=0; i<KEY_MAX; i++)
    if(KeyPressed(i))
       return true;
 return false; //no keys are down
}
