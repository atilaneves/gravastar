#ifndef _CMELEE_SERVER_H_
#define _CMELEE_SERVER_H_


class CGravOptions;
#include "CTcpServer.hpp"
#include "CGravConnection.hpp"
#include <thread>
#include <vector>


class CMeleeServer: public CTcpConnectionObserver {
public:

    CMeleeServer();
    ~CMeleeServer();
    void SendFrame(const std::vector<unsigned char>& frameBytes);
    void SendOptions(const CGravOptions& gravOptions);
    virtual void Handle(const CTcpConnection::Pointer& tcpConnection) override;

private:

    boost::asio::io_service mTcpIoService;
    CTcpServer mTcpServer;
    std::thread mTcpThread;
    std::vector<std::unique_ptr<CGravConnection>> mConnections;
};


#endif
