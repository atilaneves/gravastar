#ifndef CUDP_CLIENT_HPP_
#define CUDP_CLIENT_HPP_


#include <vector>
#include <boost/asio.hpp>


class CUdpClient {
public:

    CUdpClient(const std::string& address, int port);
    void SendBytes(const std::vector<unsigned char>& sendBuffer);


private:

    const boost::asio::ip::udp::endpoint mServerEndpoint;
    boost::asio::io_service mService;
    boost::asio::ip::udp::socket mSocket;
};

#endif
