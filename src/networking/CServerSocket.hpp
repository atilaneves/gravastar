#ifndef _SERVER_SOCKET_H_
#define _SERVER_SOCKET_H_


class CGravOptions;
#include "CTcpServer.hpp"
#include "CGravConnection.hpp"
#include <vector>


class CServerSocket: public CTcpConnectionObserver {
public:

    CServerSocket(const CGravOptions& options);
    void SendFrame(const std::vector<unsigned char>& frameBytes);
    virtual void Handle(const CTcpConnection::Pointer& tcpConnection) override;
    void End(int winner);
    std::string GetPilotType(const std::string& type, unsigned pilotIndex) const;

private:

    std::vector<std::string> mPilotTypes;
    const CGravOptions& mGravOptions;
    CTcpServer mTcpServer;
    std::vector<std::unique_ptr<CGravConnection>> mConnections;

    void SendClientArgs();
    unsigned GetPilotIndex(unsigned connectionIndex) const;
};


#endif
