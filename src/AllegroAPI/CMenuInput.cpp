#include "CMenuInput.hpp"
#include "CKeyboard.hpp"
#include "CJoystick.hpp"


bool CMenuInput::sUp=false;
bool CMenuInput::sDown=false;
bool CMenuInput::sLeft=false;
bool CMenuInput::sRight=false;
bool CMenuInput::sSelect=false;
bool CMenuInput::sCancel=false;

namespace {

bool JoystickPressedNow(bool pressed, bool &wasPressing, bool &initialized) {
    if(!initialized) {
        wasPressing = pressed;
        initialized = true;
        return false;
    }
    if(pressed && !wasPressing) {
        wasPressing = true;
        return true;
    }
    if(!pressed)
        wasPressing = false;
    return false;
}

}


bool CMenuInput::Up() {
    static bool joyWasPressing = false, joyInitialized = false;
    const bool keyPressed = PressedNow(CKeyboard::KeyPressed(CKeyboard::kUp), sUp);
    const bool joyPressed = JoystickPressedNow(CJoystick::JoyUp(),
                                               joyWasPressing, joyInitialized);
    return keyPressed || joyPressed;
}


bool CMenuInput::Down() {
    static bool joyWasPressing = false, joyInitialized = false;
    const bool keyPressed = PressedNow(CKeyboard::KeyPressed(CKeyboard::kDown), sDown);
    const bool joyPressed = JoystickPressedNow(CJoystick::JoyDown(),
                                               joyWasPressing, joyInitialized);
    return keyPressed || joyPressed;
}


bool CMenuInput::Left() {
    static bool joyWasPressing = false, joyInitialized = false;
    const bool keyPressed = PressedNow(CKeyboard::KeyPressed(CKeyboard::kLeft), sLeft);
    const bool joyPressed = JoystickPressedNow(CJoystick::JoyLeft(),
                                               joyWasPressing, joyInitialized);
    return keyPressed || joyPressed;
}


bool CMenuInput::Right() {
    static bool joyWasPressing = false, joyInitialized = false;
    const bool keyPressed = PressedNow(CKeyboard::KeyPressed(CKeyboard::kRight), sRight);
    const bool joyPressed = JoystickPressedNow(CJoystick::JoyRight(),
                                               joyWasPressing, joyInitialized);
    return keyPressed || joyPressed;
}


bool CMenuInput::Select() {
    static bool joyWasPressing = false, joyInitialized = false;
    const bool keyPressed = PressedNow(CKeyboard::KeyPressed(CKeyboard::kEnter),
                                       sSelect);
    const bool joyPressed = JoystickPressedNow(CJoystick::JoyPressed(0),
                                               joyWasPressing, joyInitialized);
    return keyPressed || joyPressed;
}


bool CMenuInput::Cancel() {
    static bool joyWasPressing = false, joyInitialized = false;
    const bool keyPressed = PressedNow(CKeyboard::KeyPressed(CKeyboard::kEsc),
                                       sCancel);
    const bool joyPressed = JoystickPressedNow(CJoystick::JoyPressed(1),
                                               joyWasPressing, joyInitialized);
    return keyPressed || joyPressed;
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
