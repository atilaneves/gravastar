#include "CGravUpdateServer.hpp"
#include "Decerealiser.hpp"


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


void CGravUpdateServer::AfterReceive(const boost::system::error_code& error,
                                     std::size_t numBytes, const Array& bytes) {
    if(error && error != boost::asio::error::message_size) {
        return;
    }

    Decerealiser cereal(bytes);
    const auto milliseconds = cereal.read<uint32_t>();
    const auto numPilots = cereal.read<uint8_t>();
    {
        std::lock_guard<std::mutex> lock{mPilotMutex};
        mPilots.clear();
        for(unsigned p = 0; p < numPilots; ++p) {
            const auto px = cereal.read<uint16_t>();
            const auto py = cereal.read<uint16_t>();
            const float vx = static_cast<float>(cereal.read<int16_t>());
            const float vy = static_cast<float>(cereal.read<int16_t>());
            const auto teamHash = cereal.read<uint8_t>();
            const bool isAlive = cereal.read<uint8_t>();
            const bool hasSplitScreen = cereal.read<uint8_t>();

            CPilotStats* stats = nullptr;
            mPilots.push_back({CScreenPos{px, py}, CVector2{vx, vy},
                                 CTeam::FromHash(teamHash), *stats,
                                     isAlive, hasSplitScreen});
        }
    }

    const auto numSprites = cereal.read<uint16_t>();
    {
        std::lock_guard<std::mutex> lock{mSpriteMutex};
        mSprites.clear();
        for(unsigned i = 0; i < numSprites; ++i) {
            const auto spriteIndex = cereal.read<uint16_t>();
            const auto x = cereal.read<uint16_t>();
            const auto y = cereal.read<uint16_t>();
            mSprites.push_back(std::make_tuple(spriteIndex, x, y));
        }
    }
}

void CGravUpdateServer::AfterSend(const boost::system::error_code& error,
                                  std::size_t numBytes) {

}
