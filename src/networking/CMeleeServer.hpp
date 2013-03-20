#ifndef _CMELEE_SERVER_H_
#define _CMELEE_SERVER_H_

#include <thread>

class CUdpServer;

class CMeleeServer {
public:

    CMeleeServer();
    ~CMeleeServer();

private:

    CUdpServer* mUdpServer;
    std::thread mThread;
};


#endif
