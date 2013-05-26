#include "CGravUpdateServer.hpp"
#include "Decerealiser.hpp"


CGravUpdateServer::CGravUpdateServer() {

}

auto CGravUpdateServer::GetSprites() const -> Sprites {
    std::lock_guard<std::mutex> lock{mFrameMutex};
    return mFrame.sprites;
}

auto CGravUpdateServer::GetPilots() const -> Pilots {
    std::lock_guard<std::mutex> lock{mFrameMutex};
    return mFrame.pilots;
}


void CGravUpdateServer::AfterReceive(const boost::system::error_code& error,
                                     std::size_t numBytes, const Array& bytes) {
    if(error && error != boost::asio::error::message_size) {
        return;
    }


    Decerealiser cereal(bytes);
    {
        std::lock_guard<std::mutex> lock{mFrameMutex};
        mFrame = std::move(SClientFrame{});
        cereal >> mFrame;
    }
}

void CGravUpdateServer::AfterSend(const boost::system::error_code& error,
                                  std::size_t numBytes) {

}
