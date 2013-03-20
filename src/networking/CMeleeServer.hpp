#ifndef _CMELEE_SERVER_H_
#define _CMELEE_SERVER_H_

#include "CUdpServer.hpp"
#include <thread>

class CMeleeServer {
public:

    CMeleeServer();
    ~CMeleeServer();

private:

    CUdpServer mUdpServer;
    std::thread mThread;
};


#endif
