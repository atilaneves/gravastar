#include "CGravUpdateServer.hpp"
#include <iostream>
#include <stdio.h>

CGravUpdateServer::CGravUpdateServer() {

}

auto CGravUpdateServer::GetSprites() const -> Sprites {
    std::lock_guard<std::mutex> lock{mSpriteMutex};
    return mSprites;
}

void CGravUpdateServer::AfterReceive(const boost::system::error_code& error,
                                     std::size_t numBytes, const Array& bytes) {
    if(error && error != boost::asio::error::message_size) {
        return;
    }

    //std::cout << "CGravUpdateServer received " << numBytes << " bytes" << std::endl;

    //const uint32_t milliseconds = (bytes[0] << 24) + (bytes[1] << 16) + (bytes[2] << 8) + bytes[3];
    //std::cout << "Milliseconds: " << milliseconds << std::endl;

    const uint16_t numSprites = (bytes[4] << 8) + bytes[5];
    std::cout << "numSprites: " << numSprites << std::endl;

    std::lock_guard<std::mutex> lock{mSpriteMutex};
    mSprites.clear();
    for(std::size_t i = 6; i < numBytes; i += 6) {
        const uint16_t spriteIndex = (bytes[i] << 8) + bytes[i + 1];
        const uint16_t x = (bytes[i + 2] << 8) + bytes[i + 3];
        const uint16_t y = (bytes[i + 4] << 8) + bytes[i + 5];
        std::cout << "idx: " << spriteIndex << " x: " << x << " y: " << y << std::endl;
        mSprites.push_back(std::make_tuple(spriteIndex, x, y));
    }
    std::cout << std::endl;

    std::cout << "0x";
    for(std::size_t i = 0; i < numBytes; i += 1) {
        printf("%02x", (unsigned)bytes[i]);
    }
    std::cout << std::endl;


}

void CGravUpdateServer::AfterSend(const boost::system::error_code& error,
                                  std::size_t numBytes) {
    std::cout << "CGravUpdateSercer sent " << numBytes << " bytes" << std::endl;
}
