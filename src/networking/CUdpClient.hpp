#ifndef CUDP_CLIENT_HPP_
#define CUDP_CLIENT_HPP_


#include "CUdpSocket.hpp"


class CUdpClient: public CUdpSocket {
public:

    CUdpClient(const std::string& address, int port);

private:

    virtual void HandleReceive(const boost::system::error_code& error,
                               std::size_t numBytes) override {}
    virtual void HandleSend(const boost::system::error_code& error,
                            std::size_t numBytes) override {}
};

#endif
