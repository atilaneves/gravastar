#include "CMeleeServer.hpp"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <array>
#include <string>
#include <iostream>

using boost::asio::ip::udp;


class CUdpServer {
public:

    CUdpServer();
    void run();

private:

    boost::asio::io_service mService;
    boost::asio::ip::udp::socket mSocket;
    boost::asio::ip::udp::endpoint mEndpoint;
    std::array<char, 1> mRecvBuffer;
    
    void Listen();
    void HandleReceive(const boost::system::error_code& error,
                       std::size_t numBytes);
    void HandleSend(boost::shared_ptr<std::string> message,
                    const boost::system::error_code& error,
                    std::size_t bytes_transferred);
};



CUdpServer::CUdpServer():
    mSocket(mService, udp::endpoint(udp::v4(), 12345)) {
    Listen();
}

void CUdpServer::run() {
    mService.run();
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
        boost::shared_ptr<std::string> message(new std::string("Gravastar!"));

        mSocket.async_send_to(boost::asio::buffer(*message), mEndpoint,
                              boost::bind(&CUdpServer::HandleSend, this, message,
                                          boost::asio::placeholders::error,
                                          boost::asio::placeholders::bytes_transferred));
        Listen();
    }
}


void CUdpServer::HandleSend(boost::shared_ptr<std::string> message,
                            const boost::system::error_code& error,
                            std::size_t bytes_transferred) {
}

CMeleeServer::CMeleeServer():mUdpServer(new CUdpServer) {
    mUdpServer->run();
}

CMeleeServer::~CMeleeServer() {
    delete mUdpServer;
}