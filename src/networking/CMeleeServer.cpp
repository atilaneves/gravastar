#include "CMeleeServer.hpp"
#include <boost/asio.hpp>
#include <array>

using boost::asio::ip::udp;


CMeleeServer::CMeleeServer() {

    boost::asio::io_service service;
    udp::socket socket(service, udp::endpoint(udp::v4(), 12345));
    for(;;) {
        std::array<char, 1> recv_buf;
        udp::endpoint remote_endpoint;
        boost::system::error_code error;
        socket.receive_from(boost::asio::buffer(recv_buf),
                            remote_endpoint, 0, error);

        if (error && error != boost::asio::error::message_size)
            throw boost::system::system_error(error);

        const std::string message = "Why hello there";

        boost::system::error_code ignored_error;
        socket.send_to(boost::asio::buffer(message),
                       remote_endpoint, 0, ignored_error);
    }
}
