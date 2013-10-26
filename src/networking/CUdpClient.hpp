#ifndef CUDP_CLIENT_HPP_
#define CUDP_CLIENT_HPP_


#include "CUdpSocket.hpp"


class CUdpClient: public CUdpSocket {
public:

    CUdpClient(const std::string& address, int port);
    CUdpClient(boost::asio::ip::address address, int port);
};

#endif
