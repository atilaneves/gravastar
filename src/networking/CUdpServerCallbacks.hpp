#ifndef CUDP_SERVER_CALLBACKS_HPP_
#define CUDP_SERVER_CALLBACKS_HPP_

#include "CUdpServer.hpp"
#include <functional>
#include <boost/asio.hpp>


class CUdpServerCallbacks: public CUdpServer {
public:

    using ErrorCode = boost::system::error_code;
    using RecvHandler = std::function<void(ErrorCode, size_t, const Array&)>;
    using SendHandler = std::function<void(ErrorCode, size_t)>;

    CUdpServerCallbacks(const RecvHandler& recvHandler, const SendHandler& sendHandler);

private:

    RecvHandler mRecvHandler;
    SendHandler mSendHandler;

    virtual void AfterReceive(const boost::system::error_code& error,
                              std::size_t numBytes, const Array& bytes) override;
    virtual void AfterSend(const boost::system::error_code& error,
                           std::size_t numBytes) override;
};


#endif
