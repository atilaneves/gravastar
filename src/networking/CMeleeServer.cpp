#include "CMeleeServer.hpp"
#include "CUdpServer.hpp"
#include "CGravOptions.hpp"

CMeleeServer::CMeleeServer():
    mTcpServer(mTcpIoService, *this),
    mTcpThread([this]() { mTcpIoService.run(); }) {

}

CMeleeServer::~CMeleeServer() {
    mTcpIoService.stop();
    mTcpThread.join();
}

void CMeleeServer::SendFrame(const std::vector<unsigned char>& frameBytes) {
    for(auto& connection: mConnections) {
        connection->SendUdpBytes(frameBytes);
    }
}

void CMeleeServer::Handle(const CTcpConnection::Pointer& tcpConnection) {
    mConnections.emplace_back(new CGravConnection{tcpConnection});
}

void CMeleeServer::SendOptions(const CGravOptions& gravOptions) {
    std::vector<char> bytes;    
}
