#ifndef CGRAV_CONNECTION_HPP_
#define CGRAV_CONNECTION_HPP_


#include "CTcpConnection.hpp"
#include "CUdpClient.hpp"
#include <vector>


class CGravConnection {
public:

    CGravConnection(const CTcpConnection::Pointer& tcpConnection);

    void SendUdpBytes(const std::vector<unsigned char>& bytes);
    void SendTcpBytes(const std::vector<unsigned char>& bytes);
    void SendTcpBytes(const std::string& bytes);

private:

    CTcpConnection::Pointer mTcpConnection;
    CUdpClient mUdpClient;
};

#endif
