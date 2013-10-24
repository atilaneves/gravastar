#include "CUdpSocket.hpp"
#include <boost/bind.hpp>
#include <array>
#include <string>
#include <iostream>
#include <memory>


using boost::asio::ip::udp;
using boost::asio::ip::address_v4;


CUdpSocket::CUdpSocket(int port): //server
    mSocket(mService, udp::endpoint(udp::v4(), port)) { //any address

}

CUdpSocket::CUdpSocket(const std::string& address, int port): //client
    mSocket(mService),
    mEndpoint(address_v4::from_string(address), port)
{

    mSocket.open(udp::v4());
}


void CUdpSocket::SendBytes(const std::vector<unsigned char>& sendBuffer) {
    mSocket.async_send_to(boost::asio::buffer(sendBuffer), mEndpoint,
                          boost::bind(&CUdpSocket::HandleSend, this,
                                      boost::asio::placeholders::error,
                                      boost::asio::placeholders::bytes_transferred));
}
