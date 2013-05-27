#include "CMeleeServer.hpp"
#include "CUdpServer.hpp"
#include "CGravOptions.hpp"
#include "network_buffers.hpp"
#include <iostream>
#include <string>

using namespace std;

CMeleeServer::CMeleeServer(const CGravOptions& options):
    mGravOptions(options),
    mTcpServer(mTcpIoService, *this),
    mTcpThread([this]() { mTcpIoService.run(); }) {

    cout << "CMeleeServer starting\n";
}

CMeleeServer::~CMeleeServer() {
    mTcpIoService.stop();
    mTcpThread.join();
}

void CMeleeServer::SendFrame(const vector<unsigned char>& frameBytes) {
    for(auto& connection: mConnections) {
        connection->SendUdpBytes(frameBytes);
    }
}

void CMeleeServer::Handle(const CTcpConnection::Pointer& tcpConnection) {
    cout << "CMeleeServer handling new tcpConnection" << endl;
    tcpConnection->ReadBytesAsync(13, //"UdpPort" + space + 5 digits
        [this, tcpConnection](const CTcpConnection::Array& bytes, size_t numBytes) {
            const auto tokens = msgBufToDeque(bytes, numBytes);
            assert(tokens[0] == "UdpPort");
            const uint16_t udpPort = stoi(tokens[1]);
            mConnections.emplace_back(new CGravConnection{tcpConnection, udpPort});
            SendClientArgs();
        });
    cout << "CMeleeServer carrying on" << endl;
}


static string getRealPilotType(const string& type,
                               unsigned pilotIndex, unsigned connectionIndex) {
    return pilotIndex == connectionIndex ? "Human" : "Bot";
}

template<typename T>
static void writeValue(stringstream& args, T value) {
    args << value << " ";
}

void CMeleeServer::SendClientArgs() {
    auto& gravConnection = mConnections.back();
    cout << "CMeleeServer sending args to TCP connection #" <<
        gravConnection->GetIndex() << endl;

    if(gravConnection->GetIndex() >=
       mGravOptions.GetClientOptions().GetNbPilots()) {
        cerr << "Pilot index out of range: " << gravConnection->GetIndex() << endl;
        assert(false);
    }

    stringstream clientArgs;
    writeValue(clientArgs, "Start");
    writeValue(clientArgs, gravConnection->GetIndex());
    writeValue(clientArgs, mGravOptions.GetMeleeOptions().GetLevelNb());
    writeValue(clientArgs, mGravOptions.GetClientOptions().GetNbPilots());
    const auto& allPilotOpts = mGravOptions.GetClientOptions().GetAllPilotOptions();
    writeValue(clientArgs, allPilotOpts[0].GetNbShips());
    int i = 0;
    for(const auto& pilotOpts: allPilotOpts) {
        writeValue(clientArgs, pilotOpts.GetName());
        const auto type = getRealPilotType(pilotOpts.GetType(), i,
                                           gravConnection->GetIndex());
        writeValue(clientArgs, type);
        writeValue(clientArgs, pilotOpts.GetTeam().GetName());
        const auto ships = pilotOpts.GetShipNames();
        for(const auto& ship: ships) {
            writeValue(clientArgs, ship);
        }
        ++i;
    }
    cout << "Server -> Client: " << clientArgs.str() << endl;
    gravConnection->SendTcpBytes(clientArgs.str());
}

void CMeleeServer::End() {
    for(auto& connection: mConnections) {
        stringstream clientArgs{"Stop "};
        connection->SendTcpBytes(clientArgs.str());
    }
}
