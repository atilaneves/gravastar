#include "CUdpClient.hpp"

namespace asio = boost::asio;
using asio::ip::udp;
using asio::ip::address_v4;

CUdpClient::CUdpClient(const std::string& address, int port):
    mAddress{address_v4::from_string(address)} ,
    mReceiverEndpoint(mAddress, port), /*port*/
    mSocket(mService) {

    mSocket.open(udp::v4());
}


void CUdpClient::SendBytes(const std::vector<unsigned char>& sendBuffer) {
    mSocket.send_to(boost::asio::buffer(sendBuffer), mReceiverEndpoint);
}
