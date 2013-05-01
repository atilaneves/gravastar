#ifndef CTCP_CONNECTION_HPP_
#define CTCP_CONNECTION_HPP_

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;


class CTcpConnection: public boost::enable_shared_from_this<CTcpConnection> {
public:
    using Pointer = boost::shared_ptr<CTcpConnection>;

    static Pointer Create(boost::asio::io_service& io_service);
    tcp::socket& Socket();
    void Start();

private:
    tcp::socket mSocket;
    std::string mMessage;

    CTcpConnection(boost::asio::io_service& ioService);
    void HandleWrite(const boost::system::error_code& error,
                     size_t bytes_transferred);
};


#endif
