#include "CPilotProxy.hpp"
#include "CPilotFactory.hpp"


REG_PILOT("Proxy", CPilotProxy)


CPilotProxy::CPilotProxy(const CPilotOptions &options, const CShipYard &shipYard,
                         CMeleeScore& meleeScore):
    CPilot(false, /*split screen*/ options, shipYard, meleeScore) {
}

void CPilotProxy::CheckControls(CClientSocket* clientSocket) {
}
