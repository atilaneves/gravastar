#include "CGravConnection.hpp"


unsigned CGravConnection::sNumConnections = 0;


CGravConnection::CGravConnection(const CTcpConnection::Pointer& tcpConnection,
                                 int udpPort):
    mTcpConnection(tcpConnection),
    mUdpClient("127.0.0.1", udpPort),
    mIndex(++sNumConnections) {
}

CGravConnection::~CGravConnection() {
    --sNumConnections;
}

void CGravConnection::SendUdpBytes(const std::vector<unsigned char>& bytes) {
    mUdpClient.SendBytes(bytes);
}

void CGravConnection::SendTcpBytes(const std::vector<unsigned char>& bytes) {
    mTcpConnection->SendBytes(bytes);
}

void CGravConnection::SendTcpBytes(const std::string& bytes) {
    mTcpConnection->SendBytes(bytes);
}
