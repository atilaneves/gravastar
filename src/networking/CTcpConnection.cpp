#include "CTcpConnection.hpp"
#include <boost/bind.hpp>
#include <iostream>

namespace asio = boost::asio;
using namespace std;

CTcpConnection::CTcpConnection(boost::asio::io_service& ioService)
        : mSocket(ioService) {
}

auto CTcpConnection::Create(boost::asio::io_service& io_service) -> Pointer {
    return Pointer{ new CTcpConnection(io_service) };
}

boost::asio::ip::tcp::socket& CTcpConnection::Socket() {
    return mSocket;
}


void CTcpConnection::SendBytes(const std::string& bytes) {
    std::vector<unsigned char> vec;
    vec.insert(std::begin(vec), std::begin(bytes), std::end(bytes));
    SendBytes(vec);
}

void CTcpConnection::SendBytes(const std::vector<unsigned char>& bytes) {
    mSent.clear();
    mSent.insert(std::begin(mSent), std::begin(bytes), std::end(bytes));
    async_write(mSocket, asio::buffer(mSent),
                boost::bind(&CTcpConnection::HandleWrite, shared_from_this(),
                            asio::placeholders::error, asio::placeholders::bytes_transferred));
}

void CTcpConnection::ReadBytesAsync(size_t numBytes, TcpReaderFunc func) {
    cout << "CTcpConnection::ReadBytesAsync" << endl;
    mTcpReaderFunc = std::move(func);
    asio::async_read(mSocket, asio::buffer(mRecd),
                     asio::transfer_at_least(numBytes),
                     boost::bind(&CTcpConnection::HandleRead,
                                 shared_from_this(),
                                 asio::placeholders::error,
                                 asio::placeholders::bytes_transferred));
}


void CTcpConnection::HandleWrite(const boost::system::error_code& /*error*/,
                                 size_t /*bytes_transferred*/) {
}

void CTcpConnection::HandleRead(const boost::system::error_code& /*error*/,
                                size_t numBytes) {
    mTcpReaderFunc(mRecd, numBytes);
}
