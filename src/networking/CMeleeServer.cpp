#include "CMeleeServer.hpp"
#include "CUdpServer.hpp"
#include "CGravOptions.hpp"
#include "network_buffers.hpp"
#include <iostream>
#include <string>

using namespace std;

static vector<string> getPilotTypes(const CGravOptions& options) {
    vector<string> types;
    const auto& allPilotOptions = options.GetClientOptions().GetAllPilotOptions();
    for(const auto& pilotOptions: allPilotOptions) {
        types.push_back(pilotOptions.GetType());
    }
    return types;
}

CMeleeServer::CMeleeServer(const CGravOptions& options):
    mPilotTypes(getPilotTypes(options)),
    mGravOptions(options),
    mTcpServer(mTcpIoService, *this),
    mTcpThread([this]() { mTcpIoService.run(); }) {

    cout << "CMeleeServer starting\n";
}

CMeleeServer::~CMeleeServer() {
    mTcpIoService.stop();
    mTcpThread.join();
}

std::string CMeleeServer::GetPilotType(const std::string& type,
                                       unsigned pilotIndex) const {
    if(pilotIndex == 0 || type == "Bot") {
        return type;
    }
    return "Client";
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
}


static string getRealPilotType(const string& type,
                               unsigned pilotIndex, unsigned connectionIndex) {
    return pilotIndex == connectionIndex ? "Client" : "Server";
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
        cerr << "Connection index (" << gravConnection->GetIndex() <<
            ") larger than #pilots (" << mGravOptions.GetClientOptions().GetNbPilots()
             << ")" << endl;
        assert(false);
    }

    stringstream clientArgs;
    writeValue(clientArgs, "Start");
    const auto clientIndex = GetPilotIndex(gravConnection->GetIndex());
    writeValue(clientArgs, clientIndex);
    writeValue(clientArgs, mGravOptions.GetMeleeOptions().GetLevelNb());
    writeValue(clientArgs, mGravOptions.GetClientOptions().GetNbPilots());
    const auto& allPilotOpts = mGravOptions.GetClientOptions().GetAllPilotOptions();
    writeValue(clientArgs, allPilotOpts[0].GetNbShips());
    int i = 0;
    for(const auto& pilotOpts: allPilotOpts) {
        writeValue(clientArgs, pilotOpts.GetName());
        const auto type = getRealPilotType(pilotOpts.GetType(), i, clientIndex);
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

unsigned CMeleeServer::GetPilotIndex(unsigned connectionIndex) const {
    unsigned numHumans = 0;
    for(unsigned i = 0; i < mPilotTypes.size(); ++i) {
        if(numHumans == connectionIndex) return i;
        if(mPilotTypes[i] == "Human") ++numHumans;
    }
    assert(false);
    return 0;
}

void CMeleeServer::End(int winner) {
    for(auto& connection: mConnections) {
        stringstream clientArgs;
        writeValue(clientArgs, "Stop");
        writeValue(clientArgs, winner);
        connection->SendTcpBytes(clientArgs.str());
    }
}
