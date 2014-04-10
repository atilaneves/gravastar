#include "CMenuInput.hpp"
#include "CKeyboard.hpp"
#include "CJoystick.hpp"


bool CMenuInput::sUp=false;
bool CMenuInput::sDown=false;
bool CMenuInput::sLeft=false;
bool CMenuInput::sRight=false;
bool CMenuInput::sSelect=false;
bool CMenuInput::sCancel=false;


bool CMenuInput::Up() {
    return PressedNow(CKeyboard::KeyPressed(CKeyboard::kUp) ||
                      CJoystick::JoyUp(), sUp);
}


bool CMenuInput::Down() {
    return PressedNow(CKeyboard::KeyPressed(CKeyboard::kDown) ||
                      CJoystick::JoyDown(), sDown);
}


bool CMenuInput::Left() {
    return PressedNow(CKeyboard::KeyPressed(CKeyboard::kLeft) ||
                      CJoystick::JoyLeft(), sLeft);
}


bool CMenuInput::Right() {
    return PressedNow(CKeyboard::KeyPressed(CKeyboard::kRight) ||
                      CJoystick::JoyRight(), sRight);
}


bool CMenuInput::Select() {
    return PressedNow(CKeyboard::KeyPressed(CKeyboard::kEnter) ||
                      CJoystick::JoyPressed(0), sSelect);
}


bool CMenuInput::Cancel() {
    return PressedNow(CKeyboard::KeyPressed(CKeyboard::kEsc) ||
                      CJoystick::JoyPressed(1), sCancel);
}


bool CMenuInput::PressedNow(bool pressed, bool &wasPressing) {

    if(pressed && !wasPressing) {
        wasPressing = true;
        return true;
    }
    if(!pressed)
        wasPressing = false;

    return false;

}
