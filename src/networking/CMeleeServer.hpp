#ifndef _CMELEE_SERVER_H_
#define _CMELEE_SERVER_H_

#include "CUdpClient.hpp"
#include "CTcpServer.hpp"
#include <vector>
#include <thread>

class CMeleeServer {
public:

    CMeleeServer();
    ~CMeleeServer();
    void sendFrame(const std::vector<char>& frameBytes);

private:

    boost::asio::io_service mTcpIoService;
    CTcpServer mTcpServer;
    std::thread mTcpThread;
    CUdpClient mUdpClient;
};


#endif
