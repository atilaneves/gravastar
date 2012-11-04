#ifndef _CMELEE_SERVER_H_
#define _CMELEE_SERVER_H_


class CUdpServer;

class CMeleeServer {
public:

    CMeleeServer();
    ~CMeleeServer();

private:

    CUdpServer* mUdpServer;
};


#endif
