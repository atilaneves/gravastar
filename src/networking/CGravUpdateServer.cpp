#include "CGravUpdateServer.hpp"
#include "Decerealiser.hpp"
#include <iostream>


using namespace std;


CGravUpdateServer::CGravUpdateServer(uint16_t serverUdpPort, unsigned pilotIndex):
    CUdpServer(serverUdpPort),
    mPilotIndex(pilotIndex) {

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
        cerr << "Error in GravUpdateServer::AfterReceive" << endl;
        return;
    }

    Decerealiser cereal(bytes);
    UpdateFrame(cereal);
}

void CGravUpdateServer::UpdateFrame(Decerealiser& cereal) {
    std::lock_guard<std::mutex> lock{mFrameMutex};
    mFrame = std::move(SClientFrame{}); //reset
    cereal >> mFrame;
    mFrame.SetPilot(mPilotIndex);
}

void CGravUpdateServer::AfterSend(const boost::system::error_code& error,
                                  std::size_t numBytes) {

}
