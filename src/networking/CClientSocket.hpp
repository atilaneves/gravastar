#ifndef CCLIENT_SOCKET_HPP_
#define CCLIENT_SOCKET_HPP_

class Decerealiser;
class CUdpSender;
#include "SClientFrame.hpp"
#include "CPilotInputProxy.hpp"
#include <mutex>
#include <atomic>


class CClientSocket {
public:

    CClientSocket(unsigned pilotIndex, CUdpSender& udpSender);

    void UpdateFrame(Decerealiser& cereal);
    SClientFrame GetFrame() const;
    void SendControls(CPilotInputProxy input);
    bool IsReady() const { return mReady; }

private:

    unsigned mPilotIndex;
    CUdpSender& mUdpSender;
    std::atomic_bool mReady;
    SClientFrame mFrame;
    mutable std::mutex mFrameMutex;
};


#endif
