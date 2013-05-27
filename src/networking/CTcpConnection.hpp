#ifndef CTCP_CONNECTION_HPP_
#define CTCP_CONNECTION_HPP_

#include <string>
#include <functional>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>


class CTcpConnection: public boost::enable_shared_from_this<CTcpConnection> {
public:
    using Pointer = boost::shared_ptr<CTcpConnection>;
    using Bytes = std::vector<unsigned char>;
    using Array = std::array<unsigned char, 1024>;
    using TcpReaderFunc = std::function<void(const Array&, size_t)>;

    static Pointer Create(boost::asio::io_service& io_service);
    boost::asio::ip::tcp::socket& Socket();
    void SendBytes(const Bytes& bytes);
    void SendBytes(const std::string& bytes);
    void ReadBytesAsync(size_t numBytes, TcpReaderFunc func);

private:
    boost::asio::ip::tcp::socket mSocket;
    Bytes mSent;
    Array mRecd;
    TcpReaderFunc mTcpReaderFunc;

    CTcpConnection(boost::asio::io_service& ioService);
    void HandleWrite(const boost::system::error_code& error,
                     size_t bytes_transferred);
    void HandleRead(const boost::system::error_code& error,
                    size_t bytes_transferred);
};


#endif
