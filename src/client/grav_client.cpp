#include "CUdpServerCallbacks.hpp"
#include <thread>
#include <boost/asio.hpp>
#include <stdint.h>

using boost::asio::ip::tcp;
bool gDebug = false;


static void sendHandler(boost::system::error_code error, size_t bytes) {
    std::cout << "Sent " << bytes << " bytes\n";
}


static void recvHandler(boost::system::error_code error, size_t bytes,
                        const CUdpServer::Array& array) {
    if(error && error != boost::asio::error::message_size) {
        return;
    }

    std::cout << "Received " << bytes << " bytes\n";

    const uint32_t milliseconds = (array[0] << 24) + (array[1] << 16) + (array[2] << 8) + array[3];
    std::cout << "Milliseconds: " << milliseconds << std::endl; 

    const uint16_t numSprites = (array[4] << 8) + array[5];
    std::cout << "numSprites: " << numSprites << std::endl;

    for(std::size_t i = 6; i < bytes; i += 6) {
        const uint16_t spriteIndex = (array[i] << 8) + array[i + 1];
        const uint16_t x = (array[i + 2] << 8) + array[i + 3];
        const uint16_t y = (array[i + 4] << 8) + array[i + 5];
        std::cout << "idx: " << spriteIndex << " x: " << x << " y: " << y << std::endl;
    }
    std::cout << std::endl;
}


static void connectToTcpServer() {
    boost::asio::io_service service;
    tcp::socket socket(service);

    const boost::asio::ip::address_v4 addr({{0x7f, 0, 0, 1}}); //local
    tcp::endpoint receiverEndpoint(addr, 12346);
    socket.connect(receiverEndpoint);

    for (;;) {
        std::array<char, 128> buf;
        boost::system::error_code error;

        const auto len = socket.read_some(boost::asio::buffer(buf), error);

        if(error == boost::asio::error::eof) {
            continue;
            std::cout << "Connection closed by server\n";
            break; // Connection closed cleanly by peer.
        } else if(error) {
            throw boost::system::system_error(error); // Some other error.
        }

        std::cout.write(buf.data(), len);
        std::cout << std::endl;
    }
}

int main() {
    CUdpServerCallbacks udpServer(recvHandler, sendHandler);
    std::thread udpThread([&](){ udpServer.Run(); });
    
    connectToTcpServer();

    udpServer.Stop();
    udpThread.join();
}
