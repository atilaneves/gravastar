#include "CPilotClient.hpp"
#include "CPilotFactory.hpp"


REG_PILOT("Client", CPilotClient)


CPilotClient::CPilotClient(const CPilotOptions &options, const CShipYard &shipYard,
                           CMeleeScore& meleeScore):
    CPilot(false, /*split screen*/ options, shipYard, meleeScore) {
}

void CPilotClient::CheckControls() {
}
