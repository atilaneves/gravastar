#include "CUdpClient.hpp"

using boost::asio::ip::udp;

CUdpClient::CUdpClient():
    mAddress({{0x7f, 0, 0, 1}}) /*local*/,
    mReceiverEndpoint(mAddress, 12345), /*port*/
    mSocket(mService) {

    mSocket.open(udp::v4());
}

void CUdpClient::sendBytes(const std::vector<char>& sendBuffer) {
    mSocket.send_to(boost::asio::buffer(sendBuffer), mReceiverEndpoint);
}
