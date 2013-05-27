#include "CTcpServer.hpp"
#include <algorithm>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;
using namespace std;


CTcpServer::CTcpServer(boost::asio::io_service& ioService,
                       CTcpConnectionObserver& tcpObserver)
    : mTcpObserver(tcpObserver),
      mAcceptor(ioService, tcp::endpoint(tcp::v4(), 12346)) {

    StartAccept();
}

void CTcpServer::StartAccept() {
    CTcpConnection::Pointer newConnection =
        CTcpConnection::Create(mAcceptor.get_io_service());

    mAcceptor.async_accept(newConnection->Socket(),
                           boost::bind(&CTcpServer::HandleAccept, this, newConnection,
                                       boost::asio::placeholders::error));
}

void CTcpServer::HandleAccept(CTcpConnection::Pointer newConnection,
                              const boost::system::error_code& error) {
    if(!error) {
        mTcpObserver.Handle(newConnection);
        StartAccept();
    } else {
        cerr << "Error in CTcpServer::HandleAccept" << endl;
    }
}
