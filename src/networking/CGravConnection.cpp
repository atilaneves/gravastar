#include "CGravConnection.hpp"


CGravConnection::CGravConnection(const CTcpConnection::Pointer& tcpConnection):
    mTcpConnection(tcpConnection) {
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
