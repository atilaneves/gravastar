#include <iostream>
#include <array>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {

    boost::asio::io_service service;
    tcp::socket socket(service);

    const boost::asio::ip::address_v4 addr({{0x7f, 0, 0, 1}}); //local
    tcp::endpoint receiverEndpoint(addr, 12346);
    socket.connect(receiverEndpoint);

    for (;;) {
        std::array<char, 128> buf;
        boost::system::error_code error;

        const auto len = socket.read_some(boost::asio::buffer(buf), error);

        if (error == boost::asio::error::eof)
            break; // Connection closed cleanly by peer.
        else if (error)
            throw boost::system::system_error(error); // Some other error.

        std::cout.write(buf.data(), len);
        std::cout << std::endl;
    }
}
