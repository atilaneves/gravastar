#include "CPilotServer.hpp"
#include "CPilotFactory.hpp"


REG_PILOT("Server", CPilotServer)


CPilotServer::CPilotServer(const CPilotOptions &options, const CShipYard &shipYard,
                           CMeleeScore& meleeScore):
    CPilot(false, /*split screen*/ options, shipYard, meleeScore) {
}

void CPilotServer::CheckControls() {
}
