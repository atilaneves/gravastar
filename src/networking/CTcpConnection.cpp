#include "CTcpConnection.hpp"
#include <iostream>
#include <boost/bind.hpp>


CTcpConnection::CTcpConnection(boost::asio::io_service& ioService)
        : mSocket(ioService) {
}

auto CTcpConnection::Create(boost::asio::io_service& io_service) -> Pointer {
    return Pointer{ new CTcpConnection(io_service) };
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
