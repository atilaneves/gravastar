#ifndef CGRAVCLIENT_H_
#define CGRAVCLIENT_H_

#include "CTcpClient.hpp"
#include <string>

class CRootMenu;
class CVersusMenu;

//Networking client class for connecting from the menu
class CGravClient {
public:

    CGravClient(const std::string& addr, int port);

    void Run(CRootMenu& rootMenu, CVersusMenu& versusMenu);

private:

    CTcpClient mTcpClient;
    const uint16_t mServerUdpPort;
};


#endif // CGRAVCLIENT_H_
