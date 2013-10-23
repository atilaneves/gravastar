#include "CUdpClient.hpp"
#include <boost/bind.hpp>

namespace asio = boost::asio;
using asio::ip::udp;
using asio::ip::address_v4;


CUdpClient::CUdpClient(const std::string& address, int port):
    mSocket(mService),
    mServerEndpoint(address_v4::from_string(address), port)
{

    mSocket.open(udp::v4());
}


void CUdpClient::SendBytes(const std::vector<unsigned char>& sendBuffer) {
    mSocket.async_send_to(boost::asio::buffer(sendBuffer), mServerEndpoint,
                          boost::bind(&CUdpClient::HandleSend, this,
                                      boost::asio::placeholders::error,
                                      boost::asio::placeholders::bytes_transferred));
}
