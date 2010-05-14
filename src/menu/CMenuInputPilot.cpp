#include "CMenuInputPilot.hpp"
#include "CGravOptions.hpp"
#include "CPilotInputFactory.hpp"


CMenuInputPilot::CMenuInputPilot(int index, const CGravOptions& options):
  mInput(CPilotInputFactory::CreateInput(options.GetClientOptions().
					 GetPilotOptions(index).
					 GetInputOptions())) {

}


bool CMenuInputPilot::Up() {
  return PressedNow(mInput->Thrust(), mUp);
}


bool CMenuInputPilot::Down() {
  //return PressedNow(mInput->Super(), mDown);
  return false;
}


bool CMenuInputPilot::Left() {
  return PressedNow(mInput->Left(), mLeft);
}


bool CMenuInputPilot::Right() {
  return PressedNow(mInput->Right(), mRight);
}


bool CMenuInputPilot::Select() {
  return PressedNow(mInput->Weapon(), mSelect);
}


bool CMenuInputPilot::Cancel() {
  return PressedNow(mInput->Special(), mCancel) ||
         CMenuInput::Cancel();
}



