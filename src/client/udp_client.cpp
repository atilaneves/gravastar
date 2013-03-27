#include <boost/asio.hpp>
#include <iostream>
#include <array>

using boost::asio::ip::udp;


int main() {
    boost::asio::io_service service;
    udp::socket socket(service);
    socket.open(udp::v4());

    const boost::asio::ip::address_v4 addr({{0x7f, 0, 0, 1}}); //local
    udp::endpoint receiverEndpoint(addr, 12345);
    std::array<char, 1> sendBuf = {{ 0 }};
    socket.send_to(boost::asio::buffer(sendBuf), receiverEndpoint);

    std::array<char, 128> recvBuf;
    udp::endpoint senderEndpoint;
    const auto len = socket.receive_from(boost::asio::buffer(recvBuf), senderEndpoint);

    std::cout << "Received " << len << " bytes:" << std::endl;
    std::cout.write(recvBuf.data(), len);
    std::cout << std::endl;
}
