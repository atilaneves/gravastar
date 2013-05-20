#include "CMeleeServer.hpp"
#include "CUdpServer.hpp"
#include "CGravOptions.hpp"
#include <iostream>
#include <string>


CMeleeServer::CMeleeServer(const CGravOptions& options):
    mGravOptions(options),
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
    std::stringstream clientArgs;
    clientArgs << "Start ";
    clientArgs << mGravOptions.GetMeleeOptions().GetLevelNb() << " ";
    clientArgs << mGravOptions.GetClientOptions().GetNbPilots() << " ";
    const auto& allPilotOpts = mGravOptions.GetClientOptions().GetAllPilotOptions();
    clientArgs << allPilotOpts[0].GetNbShips() << " ";
    for(const auto& pilotOpts: allPilotOpts) {
        clientArgs << pilotOpts.GetName() << " ";
        clientArgs << pilotOpts.GetType() << " ";
        clientArgs << pilotOpts.GetTeam().GetName() << " ";
        const auto ships = pilotOpts.GetShipNames();
        for(const auto& ship: ships) {
            clientArgs << ship << " ";
        }
    }
    tcpConnection->SendBytes(clientArgs.str());
    mConnections.emplace_back(new CGravConnection{tcpConnection});
}

void CMeleeServer::End() {
    for(auto& connection: mConnections) {
        std::stringstream clientArgs{"Stop "};
        connection->SendTcpBytes(clientArgs.str());
    }
}
