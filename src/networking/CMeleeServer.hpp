#ifndef _CMELEE_SERVER_H_
#define _CMELEE_SERVER_H_

#include "CUdpServer.hpp"
#include "CTcpServer.hpp"
#include <thread>

class CMeleeServer {
public:

    CMeleeServer();
    ~CMeleeServer();

private:

    CUdpServer mUdpServer;
    boost::asio::io_service mTcpIoService;
    CTcpServer mTcpServer;
    std::thread mUdpThread;
    std::thread mTcpThread;
};


#endif
