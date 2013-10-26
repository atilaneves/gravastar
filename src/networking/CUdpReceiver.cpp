#include "CUdpReceiver.hpp"
#include <boost/bind.hpp>
#include <array>
#include <string>
#include <iostream>
#include <memory>


using boost::asio::ip::udp;
using boost::asio::ip::address_v4;


CUdpReceiver::CUdpReceiver(CUdpObserver& observer, int port):
    mObserver(observer),
    mSocket(mService, udp::endpoint(udp::v4(), port)) //any address
{

    Listen();
}


void CUdpReceiver::Run() {
    mService.run();
}


void CUdpReceiver::Stop() {
    mService.stop();
}


void CUdpReceiver::Listen() {
    boost::asio::ip::udp::endpoint endpoint;
    mSocket.async_receive_from(boost::asio::buffer(mRecvBuffer), endpoint,
                               boost::bind(&CUdpReceiver::HandleReceive, this,
                                           boost::asio::placeholders::error,
                                           boost::asio::placeholders::bytes_transferred));
}


void CUdpReceiver::HandleReceive(const boost::system::error_code& error,
                               std::size_t numBytes) {
    mObserver.UdpReceived(error, numBytes, mRecvBuffer);
    Listen();
}
