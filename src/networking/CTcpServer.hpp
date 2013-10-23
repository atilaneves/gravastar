#ifndef TCP_SERVER_HPP_
#define TCP_SERVER_HPP_

#include "CTcpConnection.hpp"
#include <thread>
#include <boost/asio.hpp>


class CTcpConnectionObserver {
public:
    virtual void HandleTcpConnection(const CTcpConnection::Pointer& tcpConnection) = 0;
};

class CTcpServer {
public:

    CTcpServer(int port, CTcpConnectionObserver& tcpObserver);
    ~CTcpServer();

private:

    boost::asio::io_service mIoService;
    CTcpConnectionObserver& mTcpObserver;
    boost::asio::ip::tcp::acceptor mAcceptor;
    std::thread mThread;

    void Accept();
    void HandleAccept(CTcpConnection::Pointer newConnection,
                      const boost::system::error_code& error);
};


#endif
