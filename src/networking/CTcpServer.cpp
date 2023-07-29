#include "CTcpServer.hpp"
#include <algorithm>
#include <boost/bind/bind.hpp>
#include <iostream>


using boost::asio::ip::tcp;
using namespace std;


CTcpServer::CTcpServer(CTcpConnectionObserver& tcpObserver, int port):
    mTcpObserver(tcpObserver),
    mAcceptor(mIoService, tcp::endpoint(tcp::v4(), port)),
    mThread([this]{ mIoService.run();})
{

    Accept();
}

CTcpServer::~CTcpServer() {
    mIoService.stop();
    mThread.join();
}

void CTcpServer::Accept() {
    // auto newConnection = CTcpConnection::Create(mAcceptor.get_io_service());

    // mAcceptor.async_accept(newConnection->Socket(),
    //                        boost::bind(&CTcpServer::HandleAccept, this, newConnection,
    //                                    boost::asio::placeholders::error));
}

void CTcpServer::HandleAccept(CTcpConnection::Pointer newConnection,
                              const boost::system::error_code& error) {
    if(!error) {
        mTcpObserver.HandleTcpConnection(newConnection);
        Accept();
    } else {
        cerr << "Error in CTcpServer::HandleAccept" << endl;
    }
}
