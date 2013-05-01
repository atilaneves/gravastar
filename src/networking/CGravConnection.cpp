#include "CGravConnection.hpp"


CGravConnection::CGravConnection(const CTcpConnection::Pointer& tcpConnection):
    mTcpConnection(tcpConnection) {
}

void CGravConnection::SendBytes(const std::vector<char>& frameBytes) {
    mUdpClient.SendBytes(frameBytes);
}
