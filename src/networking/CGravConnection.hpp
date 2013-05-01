#ifndef CGRAV_CONNECTION_HPP_
#define CGRAV_CONNECTION_HPP_


#include "CTcpConnection.hpp"
#include "CUdpClient.hpp"
#include <vector>


class CGravConnection {
public:

    CGravConnection(const CTcpConnection::Pointer& tcpConnection);

    void SendBytes(const std::vector<char>& frameBytes);

private:

    CTcpConnection::Pointer mTcpConnection;
    CUdpClient mUdpClient;
};

#endif
