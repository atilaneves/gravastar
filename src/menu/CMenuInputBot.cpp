#include "CMenuInputBot.hpp"
#include "CMenuInputPilot.hpp"


CMenuInputBot::CMenuInputBot(CMenuInputPilot &menuInputPilot):
  mActive(false) {
  menuInputPilot.AddBot(this);
}
  

bool CMenuInputBot::Up() {
  return mActive ? CMenuInput::Up() : false;
}

bool CMenuInputBot::Down() {
  return mActive ? CMenuInput::Down() : false;
}

bool CMenuInputBot::Left() {
  return mActive ? CMenuInput::Left() : false;
}

bool CMenuInputBot::Right() {
  return mActive ? CMenuInput::Right() : false;
}

bool CMenuInputBot::Select() {
  return mActive ? CMenuInput::Select() : false;
}

bool CMenuInputBot::Cancel() {
  return mActive ? CMenuInput::Cancel() : false;
}
