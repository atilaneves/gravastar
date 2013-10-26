#include "CPilotHuman.hpp"
#include "CPilotFactory.hpp"
#include "CMeleeScore.hpp"


REG_PILOT("Human", CPilotHuman)


CPilotHuman::CPilotHuman(const CPilotOptions &options,
                         const CShipYard &shipYard,
                         CMeleeScore& meleeScore):
    CPilot(true /*splitscreen*/, options, shipYard, meleeScore),
    mReleasedStart(true) {

}


void CPilotHuman::CheckControls(CClientSocket* clientSocket) {
    GetShip().ApplyInput(*mInput);
    if(mInput->Start() && mReleasedStart) {
        mReleasedStart = false;
        mMeleeScore.Draw(GetIndex(), "Pause", *mInput);
    }
    if(!mInput->Start()) mReleasedStart = true;
}
