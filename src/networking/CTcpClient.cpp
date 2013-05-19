#include "CTcpClient.hpp"


CTcpClient::CTcpClient(const std::string& addr, int port):
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


bool CTcpClient::ReadForever(const MsgHandler& msgHandler) {
    std::cout << "ReadForever" << std::endl;
    for (;;) {
        std::array<unsigned char, 1024> buf;
        boost::system::error_code error;

        const auto len = mSocket.read_some(boost::asio::buffer(buf), error);
        std::cout << "Read " << len << " bytes" << std::endl;

        if(error == boost::asio::error::eof) {
            std::cout << "Connection closed by server. Received:" << std::endl;
            return true; // Connection closed cleanly by peer.
        } else if(error) {
            std::cerr << "Error reading bytes from server" << std::endl;
            //throw boost::system::system_error(error); // Some other error.
            return false;
        }

        std::cout << "Calling Msg HAndler" << std::endl;
        msgHandler(buf, len);
    }

    return true;
}
