#include "CPilotInputJoy.hpp"
#include "CPilotInputOptions.hpp"
#include "CJoystick.hpp"


CPilotInputJoy::CPilotInputJoy(const CPilotInputOptions& options):
  mLeft(options.Left()), mRight(options.Right()),
  mThrust(options.Thrust()), mWeapon(options.Weapon()),
  mSpecial(options.Special()), mSuper(options.Super()),
  mStart(options.Start()), mIndex(options.GetIndex()) {
}


bool CPilotInputJoy::Left() const {
  return CJoystick::JoyLeft(mIndex);
}


bool CPilotInputJoy::Right() const {
  return CJoystick::JoyRight(mIndex);
}


bool CPilotInputJoy::Thrust() const {
  return CJoystick::JoyPressed(mThrust, mIndex);
}


bool CPilotInputJoy::Weapon() const {
  return CJoystick::JoyPressed(mWeapon, mIndex) &&
        !CJoystick::JoyPressed(mSpecial, mIndex);
}


bool CPilotInputJoy::Special() const {
return CJoystick::JoyPressed(mSpecial, mIndex) &&
      !CJoystick::JoyPressed(mWeapon, mIndex);
}


bool CPilotInputJoy::Super() const {
  return mStart != mSuper ?   CJoystick::JoyPressed(mSuper, mIndex) :
    CJoystick::JoyPressed(mSpecial, mIndex) &&
    CJoystick::JoyPressed(mWeapon, mIndex);
}


bool CPilotInputJoy::Start() const {
  return CJoystick::JoyPressed(mStart, mIndex);
}
