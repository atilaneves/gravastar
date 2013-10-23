#include "CClientSocket.hpp"
#include "Decerealiser.hpp"
#include <iostream>


using namespace std;


CClientSocket::CClientSocket(int serverUdpPort, unsigned pilotIndex):
    mUdpServer(serverUdpPort, *this),
    mPilotIndex(pilotIndex) {

}

SClientFrame CClientSocket::GetFrame() const {
    lock_guard<mutex> lock{mFrameMutex};
    return mFrame;
}

void CClientSocket::UdpReceived(const boost::system::error_code& error,
                                size_t numBytes, const Array& bytes) {
    if(error && error != boost::asio::error::message_size) {
        cerr << "Error in Clientsocket::AfterReceive" << endl;
        return;
    }

    Decerealiser cereal(bytes);
    UpdateFrame(cereal);
}

void CClientSocket::UpdateFrame(Decerealiser& cereal) {
    lock_guard<mutex> lock{mFrameMutex};
    mFrame = move(SClientFrame{}); //reset
    cereal >> mFrame;
    mFrame.SetPilot(mPilotIndex);
}
