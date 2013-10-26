#ifndef CUDPSERVER_HPP_
#define CUDPSERVER_HPP_


#include <boost/asio.hpp>
#include <thread>


class CUdpObserver {
public:

    using Array = std::array<unsigned char, 1024*1024>;

    virtual void UdpReceived(const boost::system::error_code& error,
                             std::size_t numBytes, const Array& bytes) = 0;
};


class CUdpReceiver {
public:

    using Array = CUdpObserver::Array;

    CUdpReceiver(CUdpObserver& observer, int port = 0);
    ~CUdpReceiver();

    int GetPort() const { return mSocket.local_endpoint().port(); }

private:

    CUdpObserver& mObserver;
    boost::asio::io_service mService;
    boost::asio::ip::udp::socket mSocket;
    std::thread mThread;
    Array mRecvBuffer;

    void Listen();
    void HandleReceive(const boost::system::error_code& error,
                       std::size_t numBytes);
};


#endif
