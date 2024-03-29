#ifndef CGRAV_CONNECTION_HPP_
#define CGRAV_CONNECTION_HPP_


#include "CTcpConnection.hpp"
#include "CUdpSender.hpp"
#include <vector>


class CGravConnection {
public:

    CGravConnection(const CTcpConnection::Pointer& tcpConnection,
                    int udpPort);
    ~CGravConnection();

    void SendUdpBytes(const std::vector<unsigned char>& bytes);
    void SendTcpBytes(const std::vector<unsigned char>& bytes);
    void SendTcpBytes(const std::string& bytes);
    unsigned GetIndex() const { return mIndex; }

private:

    CTcpConnection::Pointer mTcpConnection;
    CUdpSender mUdpSender;
    unsigned mIndex;
    static unsigned sNumConnections;
};

#endif
