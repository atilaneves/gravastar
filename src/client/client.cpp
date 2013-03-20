#include <boost/asio.hpp>
#include <iostream>
#include <array>

using boost::asio::ip::udp;

int main() {
    boost::asio::io_service service;
    const boost::asio::ip::address_v4 addr({{0x7f, 0, 0, 1}}); //local
    udp::endpoint receiver_endpoint(addr, 12345);

    udp::socket socket(service);
    socket.open(udp::v4());

    std::array<char, 1> sendBuf  = {{ 0 }};
    socket.send_to(boost::asio::buffer(sendBuf), receiver_endpoint);

    std::array<char, 128> recvBuf;
    udp::endpoint sender_endpoint;
    size_t len = socket.receive_from(
        boost::asio::buffer(recvBuf), sender_endpoint);
    
    std::cout << "Received " << len << " bytes:" << std::endl;
    std::cout.write(recvBuf.data(), len);
    std::cout << std::endl;
    //std::cout << recv

}
