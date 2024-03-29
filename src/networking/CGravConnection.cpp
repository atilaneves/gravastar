#include "CGravConnection.hpp"


unsigned CGravConnection::sNumConnections = 0;


CGravConnection::CGravConnection(const CTcpConnection::Pointer& tcpConnection,
                                 int udpPort):
    mTcpConnection(tcpConnection),
    mUdpSender(tcpConnection->Socket().remote_endpoint().address(), udpPort),
    mIndex(++sNumConnections) {
}

CGravConnection::~CGravConnection() {
    --sNumConnections;
}

void CGravConnection::SendUdpBytes(const std::vector<unsigned char>& bytes) {
    mUdpSender.SendBytes(bytes);
}

void CGravConnection::SendTcpBytes(const std::vector<unsigned char>& bytes) {
    mTcpConnection->SendBytes(bytes);
}

void CGravConnection::SendTcpBytes(const std::string& bytes) {
    mTcpConnection->SendBytes(bytes);
}
