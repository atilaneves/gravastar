#ifndef _CMELEE_SERVER_H_
#define _CMELEE_SERVER_H_

#include "CUdpClient.hpp"
#include "CTcpServer.hpp"
#include <thread>

class CMeleeServer {
public:

    CMeleeServer();
    ~CMeleeServer();

private:

    boost::asio::io_service mTcpIoService;
    CTcpServer mTcpServer;
    std::thread mTcpThread;
    CUdpClient mUdpClient;
};


#endif
