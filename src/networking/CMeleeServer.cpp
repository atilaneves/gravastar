#include "CMeleeServer.hpp"
#include "CUdpServer.hpp"


CMeleeServer::CMeleeServer():
    mTcpServer(mTcpIoService),
    mTcpThread([this]() { mTcpIoService.run(); }) {

}

CMeleeServer::~CMeleeServer() {
    mTcpIoService.stop();
    mTcpThread.join();
}
