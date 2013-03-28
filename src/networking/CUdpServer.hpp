
#ifndef CUDPSERVER_HPP_
#define CUDPSERVER_HPP_

#include <functional>
#include <boost/asio.hpp>


class CUdpServer {
public:

    using ErrorCode = boost::system::error_code;
    using Array = std::array<char, 1024*1024>;
    using RecvHandler = std::function<void(ErrorCode, size_t, const Array&)>;
    using SendHandler = std::function<void(ErrorCode, size_t)>;

    CUdpServer(const RecvHandler& recvHandler, const SendHandler& sendHandler);
    void Run();
    void Stop();
    void SendBytes(const std::vector<char>& sendBuffer);

private:

    RecvHandler mRecvHandler;
    SendHandler mSendHandler;
    boost::asio::io_service mService;
    boost::asio::ip::udp::socket mSocket;
    boost::asio::ip::udp::endpoint mEndpoint;
    Array mRecvBuffer;
    
    void Listen();
    void HandleReceive(const boost::system::error_code& error,
                       std::size_t numBytes);
    void HandleSend(std::shared_ptr<std::string> message,
                    const boost::system::error_code& error,
                    std::size_t bytes_transferred);
};


#endif
