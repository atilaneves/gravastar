#include "CTcpConnection.hpp"
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


void CTcpConnection::Start(const std::string& startMsg) {
    SendBytes(startMsg);
}

void CTcpConnection::SendBytes(const std::string& bytes) {
    std::vector<unsigned char> vec;
    vec.insert(std::begin(vec), std::begin(bytes), std::end(bytes));
    SendBytes(vec);
}

void CTcpConnection::SendBytes(const std::vector<unsigned char>& bytes) {
    mMessage.clear();
    mMessage.insert(std::begin(mMessage), std::begin(bytes), std::end(bytes));
    boost::asio::async_write(mSocket, boost::asio::buffer(mMessage),
                             boost::bind(&CTcpConnection::HandleWrite, shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

void CTcpConnection::HandleWrite(const boost::system::error_code& /*error*/,
                                 size_t /*bytes_transferred*/) {
}
