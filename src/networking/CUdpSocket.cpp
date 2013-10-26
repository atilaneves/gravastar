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
    CUdpSocket(address_v4::from_string(address), port)
{
}


CUdpSocket::CUdpSocket(boost::asio::ip::address address, int port): //client
    mSocket(mService),
    mEndpoint(address, port)
{

    mSocket.open(udp::v4());
}
