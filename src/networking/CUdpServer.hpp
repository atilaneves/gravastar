#ifndef CUDPSERVER_HPP_
#define CUDPSERVER_HPP_

#include <boost/asio.hpp>


class CUdpObserver {
public:

    using Array = std::array<unsigned char, 1024*1024>;

    virtual void UdpReceived(const boost::system::error_code& error,
                             std::size_t numBytes, const Array& bytes) = 0;
    virtual void UdpSent(const boost::system::error_code& error, std::size_t numBytes) { }
};

class CUdpServer {
public:

    using Array = CUdpObserver::Array;

    CUdpServer(int port, CUdpObserver& observer);

    void Run();
    void Stop();
    void SendBytes(const std::vector<unsigned char>& sendBuffer);

private:

    CUdpObserver& mObserver;
    boost::asio::io_service mService;
    boost::asio::ip::udp::socket mSocket;
    boost::asio::ip::udp::endpoint mEndpoint;
    Array mRecvBuffer;

    void Listen();
    void HandleReceive(const boost::system::error_code& error,
                       std::size_t numBytes);
    void HandleSend(const boost::system::error_code& error,
                    std::size_t numBytes);
};


#endif
