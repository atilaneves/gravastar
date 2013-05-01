#include "CGravUpdateServer.hpp"
#include <iostream>
#include <stdint.h>

CGravUpdateServer::CGravUpdateServer() {

}


void CGravUpdateServer::AfterReceive(const boost::system::error_code& error,
                                       std::size_t numBytes, const Array& bytes) {
    if(error && error != boost::asio::error::message_size) {
        return;
    }

    std::cout << "CGravUpdateServer received " << numBytes << " bytes" << std::endl;

    const uint32_t milliseconds = (bytes[0] << 24) + (bytes[1] << 16) + (bytes[2] << 8) + bytes[3];
    std::cout << "Milliseconds: " << milliseconds << std::endl; 

    const uint16_t numSprites = (bytes[4] << 8) + bytes[5];
    std::cout << "numSprites: " << numSprites << std::endl;

    for(std::size_t i = 6; i < numBytes; i += 6) {
        const uint16_t spriteIndex = (bytes[i] << 8) + bytes[i + 1];
        const uint16_t x = (bytes[i + 2] << 8) + bytes[i + 3];
        const uint16_t y = (bytes[i + 4] << 8) + bytes[i + 5];
        std::cout << "idx: " << spriteIndex << " x: " << x << " y: " << y << std::endl;
    }
    std::cout << std::endl;

}

void CGravUpdateServer::AfterSend(const boost::system::error_code& error,
                                  std::size_t numBytes) {
    std::cout << "CGravUpdateSercer sent " << numBytes << " bytes" << std::endl;
}


