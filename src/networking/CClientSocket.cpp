#include "CClientSocket.hpp"
#include "Decerealiser.hpp"
#include "Cerealiser.hpp"
#include "CUdpSender.hpp"
#include <iostream>


using namespace std;


CClientSocket::CClientSocket(unsigned pilotIndex, CUdpSender& udpSender):
    mPilotIndex(pilotIndex),
    mUdpSender(udpSender),
    mReady(false)
{

}

SClientFrame CClientSocket::GetFrame() const {
    lock_guard<mutex> lock{mFrameMutex};
    return mFrame;
}


void CClientSocket::UpdateFrame(Decerealiser& cereal) {
    if(!mReady) mReady = true;
    lock_guard<mutex> lock{mFrameMutex};
    mFrame = move(SClientFrame{}); //reset
    cereal >> mFrame;
    mFrame.SetPilot(mPilotIndex);
}


void CClientSocket::SendControls(CPilotInputProxy input) {
    Cerealiser cereal;
    cereal << input;
    mUdpSender.SendBytes(cereal.getBytes());
}
