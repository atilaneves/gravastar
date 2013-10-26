#ifndef CUDP_CLIENT_HPP_
#define CUDP_CLIENT_HPP_


#include <string>
#include <boost/asio.hpp>


class CUdpSender {
public:

    CUdpSender(const std::string& address, int port);
    CUdpSender(boost::asio::ip::address address, int port);

    void SendBytes(const std::vector<unsigned char>& sendBuffer);

private:

    boost::asio::io_service mService;
    boost::asio::ip::udp::socket mSocket;
    boost::asio::ip::udp::endpoint mEndpoint;
};

#endif
