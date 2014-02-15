#include "CUdpSender.hpp"


using boost::asio::ip::udp;
using boost::asio::ip::address_v4;


CUdpSender::CUdpSender(const std::string& address, int port): //client
    CUdpSender(address_v4::from_string(address), port)
{
}


CUdpSender::CUdpSender(boost::asio::ip::address address, int port): //client
    mSocket(mService),
    mEndpoint(address, port)
{

    mSocket.open(udp::v4());
}

static void handleSend(const boost::system::error_code& error,
                       std::size_t numBytes) {

}

void CUdpSender::SendBytes(const std::vector<unsigned char>& sendBuffer) {
    mSocket.async_send_to(boost::asio::buffer(sendBuffer), mEndpoint,
                          handleSend);
}
