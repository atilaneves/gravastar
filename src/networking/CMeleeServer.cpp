#include "CMeleeServer.hpp"
#include "CUdpServer.hpp"


CMeleeServer::CMeleeServer():
    mTcpServer(mTcpIoService, *this),
    mTcpThread([this]() { mTcpIoService.run(); }) {

}

CMeleeServer::~CMeleeServer() {
    mTcpIoService.stop();
    mTcpThread.join();
}

void CMeleeServer::SendFrame(const std::vector<char>& frameBytes) {
    for(auto& connection: mConnections) {
        connection->SendBytes(frameBytes);
    }
}

void CMeleeServer::Handle(const CTcpConnection::Pointer& tcpConnection) {
    mConnections.emplace_back(new CGravConnection{tcpConnection});
}
