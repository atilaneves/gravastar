#include "CPilotHuman.hpp"
#include "CPilotFactory.hpp"
#include "CMeleeScore.hpp"


REG_PILOT("Human", CPilotHuman)


CPilotHuman::CPilotHuman(const CPilotOptions &options,
			 const CShipYard &shipYard,
			 CMeleeScore& meleeScore):
  CPilot(options, shipYard, meleeScore),
  mReleasedStart(true) {


}


void CPilotHuman::CheckControls() {
  GetShip().ApplyInput(*mInput);
  if(mInput->Start() && mReleasedStart) {
    mReleasedStart = false;
    mMeleeScore.Draw(GetIndex(), "Pause", *mInput);
  }
  if(!mInput->Start()) mReleasedStart = true;
}
