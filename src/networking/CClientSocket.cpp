#include "CClientSocket.hpp"
#include "Decerealiser.hpp"
#include <iostream>


using namespace std;


CClientSocket::CClientSocket(unsigned pilotIndex):
    mPilotIndex(pilotIndex) {

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
