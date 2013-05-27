#include "CUdpClient.hpp"


using boost::asio::ip::udp;


CUdpClient::CUdpClient(int port):
    mAddress{{{0x7f, 0, 0, 1}}} /*local*/,
    mReceiverEndpoint(mAddress, port), /*port*/
    mSocket(mService) {

    mSocket.open(udp::v4());
}


void CUdpClient::SendBytes(const std::vector<unsigned char>& sendBuffer) {
    mSocket.send_to(boost::asio::buffer(sendBuffer), mReceiverEndpoint);
}
