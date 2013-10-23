#include "CUdpServer.hpp"
#include <boost/bind.hpp>
#include <array>
#include <string>
#include <iostream>
#include <memory>


using boost::asio::ip::udp;


CUdpServer::CUdpServer(int port, CUdpObserver& observer):
    mObserver(observer),
    mSocket(mService, udp::endpoint(udp::v4(), port)) { //any address

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


void CUdpServer::SendBytes(const std::vector<unsigned char>& sendBuffer) {
    mSocket.async_send_to(boost::asio::buffer(sendBuffer), mEndpoint,
                          boost::bind(&CUdpServer::HandleSend, this,
                                      boost::asio::placeholders::error,
                                      boost::asio::placeholders::bytes_transferred));
}


void CUdpServer::HandleReceive(const boost::system::error_code& error,
                               std::size_t numBytes) {
    mObserver.UdpReceived(error, numBytes, mRecvBuffer);
    Listen();
}

void CUdpServer::HandleSend(const boost::system::error_code& error, std::size_t numBytes) {
    mObserver.UdpSent(error, numBytes);
    Listen();
}
