#include "CPilotInputKey.hpp"
#include "CPilotInputOptions.hpp"
#include "CKeyboard.hpp"


CPilotInputKey::CPilotInputKey(const CPilotInputOptions& options):
  mLeft(options.Left()), mRight(options.Right()),
  mThrust(options.Thrust()), mWeapon(options.Weapon()),
  mSpecial(options.Special()), mSuper(options.Super()), mStart(options.Start()) {
}


bool CPilotInputKey::Left() const {
  return CKeyboard::KeyPressed(mLeft);
}


bool CPilotInputKey::Right() const {
  return CKeyboard::KeyPressed(mRight);
}


bool CPilotInputKey::Thrust() const {
  return CKeyboard::KeyPressed(mThrust);
}


bool CPilotInputKey::Weapon() const {
  return CKeyboard::KeyPressed(mWeapon) && !CKeyboard::KeyPressed(mSpecial);
}


bool CPilotInputKey::Special() const {
  return CKeyboard::KeyPressed(mSpecial) && !CKeyboard::KeyPressed(mWeapon);
}


bool CPilotInputKey::Super() const {
  return mStart != mSuper ?  CKeyboard::KeyPressed(mSuper) :
    CKeyboard::KeyPressed(mSpecial) && CKeyboard::KeyPressed(mWeapon);
}


bool CPilotInputKey::Start() const {
  return CKeyboard::KeyPressed(mStart);
}
