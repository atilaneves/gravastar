#include "CUdpServer.hpp"
#include <boost/bind.hpp>
#include <array>
#include <string>
#include <iostream>
#include <memory>

using boost::asio::ip::udp;


CUdpServer::CUdpServer():
    mSocket(mService, udp::endpoint(udp::v4(), 12345)) {
    Listen();
}

void CUdpServer::run() {
    mService.run();
}

void CUdpServer::stop() {
    mService.stop();
}

void CUdpServer::Listen() {
    std::cout << "Listening\n";
    mSocket.async_receive_from(
        boost::asio::buffer(mRecvBuffer), mEndpoint,
        boost::bind(&CUdpServer::HandleReceive, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
  }

void CUdpServer::HandleReceive(const boost::system::error_code& error,
                               std::size_t numBytes) {
    std::cout << "Received " << numBytes << " bytes\n";
    if(!error || error == boost::asio::error::message_size) {
        std::shared_ptr<std::string> message(new std::string("Gravastar!"));

        mSocket.async_send_to(boost::asio::buffer(*message), mEndpoint,
                              boost::bind(&CUdpServer::HandleSend, this, message,
                                          boost::asio::placeholders::error,
                                          boost::asio::placeholders::bytes_transferred));
        Listen();
    }
}


void CUdpServer::HandleSend(std::shared_ptr<std::string> message,
                            const boost::system::error_code& error,
                            std::size_t bytes_transferred) {
    std::cout << "Sent " << bytes_transferred << " bytes" << std::endl;
}
