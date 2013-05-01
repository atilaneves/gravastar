#ifndef CUDPSERVER_HPP_
#define CUDPSERVER_HPP_

#include <boost/asio.hpp>


class CUdpServer {
public:

    using Array = std::array<char, 1024*1024>;

    CUdpServer();
    virtual ~CUdpServer() { }

    void Run();
    void Stop();
    void SendBytes(const std::vector<char>& sendBuffer);

private:

    boost::asio::io_service mService;
    boost::asio::ip::udp::socket mSocket;
    boost::asio::ip::udp::endpoint mEndpoint;
    Array mRecvBuffer;
    
    void Listen();
    void HandleReceive(const boost::system::error_code& error,
                       std::size_t numBytes);
    void HandleSend(const boost::system::error_code& error,
                    std::size_t numBytes);

    virtual void AfterReceive(const boost::system::error_code& error,
                              std::size_t numBytes, const Array& bytes) = 0;
    virtual void AfterSend(const boost::system::error_code& error, std::size_t numBytes) = 0;
};


#endif
