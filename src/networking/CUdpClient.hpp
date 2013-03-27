#ifndef CUDP_CLIENT_HPP_
#define CUDP_CLIENT_HPP_

#include <vector>
#include <boost/asio.hpp>

class CUdpClient {
public:

    CUdpClient();
    void sendBytes(const std::vector<char>& sendBuffer);


private:

    const boost::asio::ip::address_v4 mAddress;
    const boost::asio::ip::udp::endpoint mReceiverEndpoint;
    boost::asio::io_service mService;
    boost::asio::ip::udp::socket mSocket;
};

#endif
