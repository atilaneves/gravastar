#include "CMenuInputPilot.hpp"
#include "CMenuInputBot.hpp"
#include "CGravOptions.hpp"
#include "CPilotInputFactory.hpp"


CMenuInputPilot::CMenuInputPilot(int index, const CGravOptions& options):
  mInput(CPilotInputFactory::CreateInput(options.GetClientOptions().
					 GetPilotOptions(index).
					 GetInputOptions())) {

}

CMenuInputPilot::~CMenuInputPilot() {
  //turn on the bot inputs when we die
  for(unsigned int i = 0; i < mBots.size(); ++i)
    mBots[i]->SetActive();
}


void CMenuInputPilot::AddBot(CMenuInputBot* bot) {
  mBots.push_back(bot);
}


bool CMenuInputPilot::Up() {
  return PressedNow(mInput->MenuUp(), mUp);
}


bool CMenuInputPilot::Down() {
  return PressedNow(mInput->MenuDown(), mDown);
}


bool CMenuInputPilot::Left() {
  return PressedNow(mInput->Left(), mLeft);
}


bool CMenuInputPilot::Right() {
  return PressedNow(mInput->Right(), mRight);
}


bool CMenuInputPilot::Select() {
  return PressedNow(mInput->MenuSelect(), mSelect);
}


bool CMenuInputPilot::Cancel() {
  return PressedNow(mInput->MenuCancel(), mCancel) ||
         CMenuInput::Cancel();
}



