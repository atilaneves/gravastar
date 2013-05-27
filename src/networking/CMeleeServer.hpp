#ifndef _CMELEE_SERVER_H_
#define _CMELEE_SERVER_H_


class CGravOptions;
#include "CTcpServer.hpp"
#include "CGravConnection.hpp"
#include <thread>
#include <vector>


class CMeleeServer: public CTcpConnectionObserver {
public:

    CMeleeServer(const CGravOptions& options);
    ~CMeleeServer();
    void SendFrame(const std::vector<unsigned char>& frameBytes);
    virtual void Handle(const CTcpConnection::Pointer& tcpConnection) override;
    void End();
    std::string GetPilotType(const std::string& type, unsigned pilotIndex) const;

private:

    std::vector<std::string> mPilotTypes;
    const CGravOptions& mGravOptions;
    boost::asio::io_service mTcpIoService;
    CTcpServer mTcpServer;
    std::thread mTcpThread;
    std::vector<std::unique_ptr<CGravConnection>> mConnections;

    void SendClientArgs();
    unsigned GetPilotIndex(unsigned connectionIndex) const;
};


#endif
