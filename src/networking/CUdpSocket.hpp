#ifndef CUDPSOCKET_HPP_
#define CUDPSOCKET_HPP_


#include <boost/asio.hpp>
#include <string>


class CUdpSocket {
public:

    using Array = std::array<unsigned char, 1024*1024>;

    void SendBytes(const std::vector<unsigned char>& sendBuffer);

protected:

    CUdpSocket(int port);
    CUdpSocket(const std::string& address, int port);

    boost::asio::io_service mService;
    boost::asio::ip::udp::socket mSocket;
    boost::asio::ip::udp::endpoint mEndpoint;
    Array mRecvBuffer;

    virtual void HandleReceive(const boost::system::error_code& error,
                               std::size_t numBytes) = 0;
    virtual void HandleSend(const boost::system::error_code& error,
                            std::size_t numBytes) = 0;
};


#endif
