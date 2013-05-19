#include "CMeleeServer.hpp"
#include "CUdpServer.hpp"
#include "CGravOptions.hpp"
#include <iostream>


CMeleeServer::CMeleeServer():
    mTcpServer(mTcpIoService, *this),
    mTcpThread([this]() { mTcpIoService.run(); }) {

    std::cout << "CMeleeServer starting\n";
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
    std::cout << "CMeleeServer starting a new TCP connection" << std::endl;
    tcpConnection->Start("Start 1 2 5 P1 Human Blue Delta Delta Delta Delta Delta P2 Bot Red Delta Delta Delta Delta Delta");
    mConnections.emplace_back(new CGravConnection{tcpConnection});
}

void CMeleeServer::SendOptions(const CGravOptions& gravOptions) {
    std::vector<char> bytes;
}
