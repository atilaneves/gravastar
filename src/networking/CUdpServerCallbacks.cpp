#include "CUdpServerCallbacks.hpp"


CUdpServerCallbacks::CUdpServerCallbacks(const RecvHandler& recvHandler, const SendHandler& sendHandler):
    mRecvHandler(recvHandler), mSendHandler(sendHandler) {
}


void CUdpServerCallbacks::AfterReceive(const boost::system::error_code& error,
                                       std::size_t numBytes, const Array& bytes) {
    mRecvHandler(error, numBytes, bytes);
}

void CUdpServerCallbacks::AfterSend(const boost::system::error_code& error,
                                    std::size_t numBytes) {
    mSendHandler(error, numBytes);
}


