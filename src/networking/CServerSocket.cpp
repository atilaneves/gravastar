#include "CServerSocket.hpp"
#include "CUdpReceiver.hpp"
#include "CGravOptions.hpp"
#include "network_buffers.hpp"
#include "Decerealiser.hpp"
#include "CPilotInputProxy.hpp"
#include "CMeleeOnServer.hpp"
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

CServerSocket::CServerSocket(const CGravOptions& options,
                             CMeleeOnServer& melee):
    mPilotTypes(getPilotTypes(options)),
    mGravOptions(options),
    mMelee(melee),
    mTcpServer(*this, options.GetServerPort()),
    mUdpReceiver(*this, options.GetServerPort())
{

    sleep(2);
}


void CServerSocket::SendFrame(const vector<unsigned char>& frameBytes) {
    for(auto& connection: mConnections) {
        connection->SendUdpBytes(frameBytes);
    }
}

void CServerSocket::HandleTcpConnection(const CTcpConnection::Pointer& tcpConnection) {
    cout << "CServerSocket handling new tcpConnection" << endl;
    tcpConnection->ReadBytesAsync(13, //"UdpPort" + space + 5 digits
        [this, tcpConnection](const CTcpConnection::Array& bytes, size_t numBytes) {
            const auto tokens = msgBufToDeque(bytes, numBytes);
            assert(tokens[0] == "UdpPort");
            const uint16_t remoteUdpPort = stoi(tokens[1]);
            mConnections.emplace_back(new CGravConnection{tcpConnection, remoteUdpPort});
            SendClientArgs();
    });
}


static string getRealClientPilotType(const string& type,
                                     unsigned pilotIndex, unsigned connectionIndex) {
    return pilotIndex == connectionIndex ? "Client" : "Proxy";
}

template<typename T>
static void writeValue(stringstream& args, T value) {
    args << value << " ";
}

void CServerSocket::SendClientArgs() {
    auto& gravConnection = mConnections.back();
    cout << "CServerSocket sending args to TCP connection #" <<
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
        const auto type = getRealClientPilotType(pilotOpts.GetType(), i, clientIndex);
        writeValue(clientArgs, type);
        writeValue(clientArgs, pilotOpts.GetTeam().GetName());
        for(const auto& shipName: pilotOpts.GetShipNames()) {
            writeValue(clientArgs, shipName);
        }
        ++i;
    }
    cout << "Server -> Client: " << clientArgs.str() << endl;
    gravConnection->SendTcpBytes(clientArgs.str());
}

unsigned CServerSocket::GetPilotIndex(unsigned connectionIndex) const {
    unsigned numHumans = 0;
    for(unsigned i = 0; i < mPilotTypes.size(); ++i) {
        if(numHumans == connectionIndex) return i;
        if(mPilotTypes[i] == "Human") ++numHumans;
    }
    assert(false);
    return 0;
}

void CServerSocket::End(int winner) {
    for(auto& connection: mConnections) {
        stringstream clientArgs;
        writeValue(clientArgs, "Stop");
        writeValue(clientArgs, winner);
        connection->SendTcpBytes(clientArgs.str());
    }
}

void CServerSocket::UdpReceived(const boost::system::error_code& error,
                                std::size_t numBytes, const Array& bytes) {
    if(error && error != boost::asio::error::message_size) {
        std::cerr << "Error in CGravClient::AfterReceive" << std::endl;
        return;
    }

    cout << "UdpReceived\n";

    Decerealiser cereal{bytes};
    CPilotInputProxy input;
    cereal >> input;
    mMelee.SetControls(1, input); //TODO: use proper pilotIndex
}
