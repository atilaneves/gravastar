#include "CGravUpdateServer.hpp"
#include <iostream>


CGravUpdateServer::CGravUpdateServer() {

}

auto CGravUpdateServer::GetSprites() const -> Sprites {
    std::lock_guard<std::mutex> lock{mSpriteMutex};
    return mSprites;
}

auto CGravUpdateServer::GetPilots() const -> Pilots {
    std::lock_guard<std::mutex> lock{mPilotMutex};
    return mPilots;
}


static uint8_t readUInt8(const unsigned char*& bytes) {
    return *bytes++;
}

static uint16_t readUInt16(const unsigned char*& bytes) {
    return (static_cast<uint16_t>(readUInt8(bytes)) << 8) + readUInt8(bytes);
}

static uint16_t readInt16(const unsigned char*& bytes) {
    const auto uvalue = readUInt16(bytes);
    const auto ptr = reinterpret_cast<const int16_t*>(&uvalue);
    return *ptr;
}

static uint32_t readUInt32(const unsigned char*& bytes) {
    return (static_cast<uint32_t>(readUInt16(bytes)) << 16) + readUInt16(bytes);
}


void CGravUpdateServer::AfterReceive(const boost::system::error_code& error,
                                     std::size_t numBytes, const Array& bytes) {
    if(error && error != boost::asio::error::message_size) {
        return;
    }

    auto bytesPtr = bytes.data();
    const auto milliseconds = readUInt32(bytesPtr);
    const auto numPilots = readUInt8(bytesPtr);
    {
        std::lock_guard<std::mutex> lock{mPilotMutex};
        mPilots.clear();
        for(unsigned p = 0; p < numPilots; ++p) {
            const auto px = readUInt16(bytesPtr);
            const auto py = readUInt16(bytesPtr);
            const float vx = static_cast<float>(readInt16(bytesPtr));
            const float vy = static_cast<float>(readInt16(bytesPtr));
            const auto teamHash = readUInt8(bytesPtr);
            const bool isAlive = readUInt8(bytesPtr);
            const bool hasSplitScreen = readUInt8(bytesPtr);
            std::cout << "Client: " << px << "," << py <<
            "; " << vx << "," << vy <<
                "; " << CTeam::FromHash(teamHash).GetName() << "; " <<
                isAlive << " " << hasSplitScreen << std::endl;

            CPilotStats* stats = nullptr;
            mPilots.push_back({CScreenPos{px, py}, CVector2{vx, vy},
                                 CTeam::FromHash(teamHash), *stats,
                                     isAlive, hasSplitScreen});
        }
    }

    const auto numSprites = readUInt16(bytesPtr);
    {
        std::lock_guard<std::mutex> lock{mSpriteMutex};
        mSprites.clear();
        for(unsigned i = 0; i < numSprites; ++i) {
            const auto spriteIndex = readUInt16(bytesPtr);
            const auto x = readUInt16(bytesPtr);
            const auto y = readUInt16(bytesPtr);
            mSprites.push_back(std::make_tuple(spriteIndex, x, y));
        }
    }
}

void CGravUpdateServer::AfterSend(const boost::system::error_code& error,
                                  std::size_t numBytes) {

}
