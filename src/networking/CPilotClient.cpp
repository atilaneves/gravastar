#include "CPilotClient.hpp"
#include "CPilotFactory.hpp"
#include "CPilotInputProxy.hpp"
#include "CClientSocket.hpp"


REG_PILOT("Client", CPilotClient)


CPilotClient::CPilotClient(const CPilotOptions &options, const CShipYard &shipYard,
                           CMeleeScore& meleeScore):
    CPilot(true, /*split screen*/ options, shipYard, meleeScore) {
}

void CPilotClient::CheckControls(CClientSocket* clientSocket) {
    clientSocket->SendControls({mInput->Left(), mInput->Right(), mInput->Thrust(),
                                mInput->Weapon(), mInput->Special(), mInput->Super(),
                                mInput->Start()});
}
