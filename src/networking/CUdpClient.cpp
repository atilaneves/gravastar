#include "CUdpClient.hpp"


CUdpClient::CUdpClient(const std::string& address, int port):
    CUdpSocket(address, port)
{

}

CUdpClient::CUdpClient(boost::asio::ip::address address, int port):
    CUdpSocket(address, port)
{
}

static void handleSend(const boost::system::error_code& error,
                       std::size_t numBytes) {

}

void CUdpSocket::SendBytes(const std::vector<unsigned char>& sendBuffer) {
    mSocket.async_send_to(boost::asio::buffer(sendBuffer), mEndpoint,
                          handleSend);
}
