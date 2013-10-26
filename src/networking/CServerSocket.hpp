#ifndef _SERVER_SOCKET_H_
#define _SERVER_SOCKET_H_


class CGravOptions;
#include "CTcpServer.hpp"
#include "CUdpReceiver.hpp"
#include "CGravConnection.hpp"
#include <vector>


class CServerSocket: public CTcpConnectionObserver, public CUdpObserver {
public:

    CServerSocket(const CGravOptions& options);

    void SendFrame(const std::vector<unsigned char>& frameBytes);
    void End(int winner);
    std::string GetPilotType(const std::string& type, unsigned pilotIndex) const;

    virtual void HandleTcpConnection(const CTcpConnection::Pointer& tcpConnection) override;
    virtual void UdpReceived(const boost::system::error_code& error,
                             std::size_t numBytes, const Array& bytes) override;

private:

    std::vector<std::string> mPilotTypes;
    const CGravOptions& mGravOptions;
    CTcpServer mTcpServer;
    CUdpReceiver mUdpReceiver;
    std::vector<std::unique_ptr<CGravConnection>> mConnections;

    void SendClientArgs();
    unsigned GetPilotIndex(unsigned connectionIndex) const;
};


#endif
