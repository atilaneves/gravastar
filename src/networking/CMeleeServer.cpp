#include "CMeleeServer.hpp"
#include "CUdpServer.hpp"


CMeleeServer::CMeleeServer():
    mTcpServer(mTcpIoService),
    mUdpThread([this]() { mUdpServer.Run(); }),
    mTcpThread([this]() { mTcpIoService.run(); }) {

}

CMeleeServer::~CMeleeServer() {
    mUdpServer.Stop();
    mUdpThread.join();
    mTcpIoService.stop();
    mTcpThread.join();
}
