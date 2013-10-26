#include "CUdpServer.hpp"
#include <boost/bind.hpp>
#include <array>
#include <string>
#include <iostream>
#include <memory>


using boost::asio::ip::udp;


CUdpServer::CUdpServer(CUdpObserver& observer, int port):
    CUdpSocket(port),
    mObserver(observer) {

    Listen();
}


void CUdpServer::Run() {
    mService.run();
}


void CUdpServer::Stop() {
    mService.stop();
}


void CUdpServer::Listen() {
    mSocket.async_receive_from(boost::asio::buffer(mRecvBuffer), mEndpoint,
                               boost::bind(&CUdpServer::HandleReceive, this,
                                           boost::asio::placeholders::error,
                                           boost::asio::placeholders::bytes_transferred));
}


void CUdpServer::HandleReceive(const boost::system::error_code& error,
                               std::size_t numBytes) {
    mObserver.UdpReceived(error, numBytes, mRecvBuffer);
    Listen();
}
