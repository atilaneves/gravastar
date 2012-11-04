#include <boost/asio.hpp>
#include <iostream>
#include <array>

using boost::asio::ip::udp;

int main(int argc, char* argv[]) {
    boost::asio::io_service service;
    udp::resolver resolver(service);
    udp::resolver::query query(udp::v4(), argv[1], "Gravastar");
    udp::endpoint endpoint = *resolver.resolve(query);

}
