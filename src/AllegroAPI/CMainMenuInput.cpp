#include "CMainMenuInput.hpp"
#include "CMenuInputKey.hpp"


bool CMainMenuInput::Up() {
  return CMenuInputKey::sUp.Pressed();
}


bool CMainMenuInput::Down() {
  return CMenuInputKey::sDown.Pressed();
}


bool CMainMenuInput::Left() {
  return CMenuInputKey::sLeft.Pressed();
}


bool CMainMenuInput::Right() {
  return CMenuInputKey::sRight.Pressed();
}


bool CMainMenuInput::Select() {
  return CMenuInputKey::sSelect.Pressed();
}


bool CMainMenuInput::Cancel() {
  return CMenuInputKey::sCancel.Pressed();
}
