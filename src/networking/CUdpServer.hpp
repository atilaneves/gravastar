#ifndef CUDPSERVER_HPP_
#define CUDPSERVER_HPP_

#include "CUdpSocket.hpp"
#include <boost/asio.hpp>


class CUdpObserver {
public:

    using Array = CUdpSocket::Array;

    virtual void UdpReceived(const boost::system::error_code& error,
                             std::size_t numBytes, const Array& bytes) = 0;
    virtual void UdpSent(const boost::system::error_code& error, std::size_t numBytes) { }
};


class CUdpServer:public CUdpSocket {
public:

    CUdpServer(CUdpObserver& observer, int port = 0);

    void Run();
    void Stop();

private:

    CUdpObserver& mObserver;

    void Listen();
    virtual void HandleReceive(const boost::system::error_code& error,
                               std::size_t numBytes);
};


#endif
