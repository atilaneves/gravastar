#ifndef CUDPSERVER_HPP_
#define CUDPSERVER_HPP_

#include <boost/asio.hpp>


class CUdpServer {
public:

    CUdpServer();
    void run();
    void stop();

private:

    boost::asio::io_service mService;
    boost::asio::ip::udp::socket mSocket;
    boost::asio::ip::udp::endpoint mEndpoint;
    std::array<char, 1> mRecvBuffer;
    
    void Listen();
    void HandleReceive(const boost::system::error_code& error,
                       std::size_t numBytes);
    void HandleSend(std::shared_ptr<std::string> message,
                    const boost::system::error_code& error,
                    std::size_t bytes_transferred);
};


#endif
