#include <boost/asio.hpp>
#include <iostream>
#include <array>

using boost::asio::ip::udp;

int main(int argc, char* argv[]) {
    boost::asio::io_service service;
    udp::resolver resolver(service);
    udp::resolver::query query(udp::v4(), argv[1], "Gravastar");
    udp::endpoint endpoint = *resolver.resolve(query);

    udp::socket socket(service);
    socket.open(udp::v4());

    std::array<char, 1> sendBuf  = {{ 0 }};
    socket.send_to(boost::asio::buffer(sendBuf), endpoint);

    std::array<char, 128> recvBuf;
    udp::endpoint sender_endpoint;
    size_t len = socket.receive_from(
        boost::asio::buffer(recvBuf), sender_endpoint);

    std::cout.write(recvBuf.data(), len);
}
