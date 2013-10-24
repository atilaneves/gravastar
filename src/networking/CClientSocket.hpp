#ifndef CCLIENT_SOCKET_HPP_
#define CCLIENT_SOCKET_HPP_

class Decerealiser;
class CUdpSocket;
#include "SClientFrame.hpp"
#include <mutex>
#include <atomic>


class CClientSocket {
public:

    CClientSocket(unsigned pilotIndex);

    void UpdateFrame(Decerealiser& cereal);
    SClientFrame GetFrame() const;
    bool IsReady() const { return mReady; }

private:

    unsigned mPilotIndex;
    std::atomic_bool mReady;
    SClientFrame mFrame;
    mutable std::mutex mFrameMutex;
};


#endif
