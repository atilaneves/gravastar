#include "CTcpClient.hpp"
#include "Cerealiser.hpp"
#include <iostream>

namespace asio = boost::asio;
using namespace std;

CTcpClient::CTcpClient(const string& addr, int port):
    mStop(false),
    mSocket(mIoService),
    mServerAddress(address_v4::from_string(addr)),
    mServerPort(port),
    mEndpoint(mServerAddress, mServerPort) {

}

void CTcpClient::BlockingConnect(double seconds) {
    for(;;) { //try to connect forever, block until it does
        try {
            mSocket.connect(mEndpoint);
            break;
        } catch(...) {
            continue;
        }
    }
}

bool CTcpClient::ReadUntil(std::atomic_bool& condition,
                           const MsgHandler& msgHandler) {
    while(condition) {
        array<unsigned char, 1024> buf;
        boost::system::error_code error;

        const auto len = mSocket.read_some(asio::buffer(buf), error);

        if(error == asio::error::eof) {
            cout << "Connection closed by server." << endl;
            return true; // Connection closed cleanly by peer.
        } else if(error) {
            const auto err = boost::system::system_error(error);
            throw err; // Some other error.
        }

        msgHandler(buf, len);
        if(mStop) {
            cout << "Stopping CTcpClient" << endl;
            break;
        }
    }

    return true;
}

void CTcpClient::Send(const std::vector<unsigned char>& bytes) {
    cout << "TcpClient sending " << bytes.size() << " bytes to the server: ";
    for(const auto byte: bytes) cout << static_cast<char>(byte);
    cout << endl;
    asio::write(mSocket, asio::buffer(bytes));
}
