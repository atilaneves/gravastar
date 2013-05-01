#ifndef TCP_SERVER_HPP_
#define TCP_SERVER_HPP_

#include "CTcpConnection.hpp"
#include <boost/asio.hpp>


using boost::asio::ip::tcp;


class CTcpConnectionObserver {
public:
    virtual void Handle(const CTcpConnection::Pointer& tcpConnection) = 0;
};

class CTcpServer {
public:

    CTcpServer(boost::asio::io_service& ioService,
               CTcpConnectionObserver& tcpObserver);

private:

    CTcpConnectionObserver& mTcpObserver;
    tcp::acceptor mAcceptor;    

    void StartAccept();
    void HandleAccept(CTcpConnection::Pointer newConnection,
                      const boost::system::error_code& error);
};


#endif
