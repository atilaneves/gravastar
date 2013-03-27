#include "CTcpServer.hpp"
#include <ctime>
#include <iostream>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;


CTcpConnection::CTcpConnection(boost::asio::io_service& ioService)
        : mSocket(ioService) {
}

auto CTcpConnection::Create(boost::asio::io_service& io_service) -> pointer {
    return pointer(new CTcpConnection(io_service));
}

tcp::socket& CTcpConnection::Socket() {
    return mSocket;
}


void CTcpConnection::Start() {
    mMessage = "TCP Gravastar!";

    boost::asio::async_write(mSocket, boost::asio::buffer(mMessage),
                             boost::bind(&CTcpConnection::HandleWrite, shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}


void CTcpConnection::HandleWrite(const boost::system::error_code& /*error*/,
                                 size_t /*bytes_transferred*/) {
}


CTcpServer::CTcpServer(boost::asio::io_service& ioService)
    : mAcceptor(ioService, tcp::endpoint(tcp::v4(), 12346)) {
    std::cout << "CTcpServer starting\n";
    StartAccept();
}

void CTcpServer::StartAccept() {
    std::cout << "CTcpServer starting to accept\n";
    CTcpConnection::pointer newConnection =
        CTcpConnection::Create(mAcceptor.get_io_service());

    mAcceptor.async_accept(newConnection->Socket(),
                           boost::bind(&CTcpServer::HandleAccept, this, newConnection,
                                       boost::asio::placeholders::error));
}

void CTcpServer::HandleAccept(CTcpConnection::pointer newConnection,
                              const boost::system::error_code& error) {
    if (!error) {
        newConnection->Start();
        StartAccept();
    }
}

