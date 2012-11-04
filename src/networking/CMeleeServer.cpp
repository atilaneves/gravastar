#include "CMeleeServer.hpp"
#include <boost/asio.hpp>


using boost::asio::ip::udp;


CMeleeServer::CMeleeServer() {

    boost::asio::io_service service;
    udp::socket socket(service, udp::endpoint(udp::v4(), 12345));
}
