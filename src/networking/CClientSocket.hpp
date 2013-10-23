#ifndef CCLIENT_SOCKET_HPP_
#define CCLIENT_SOCKET_HPP_

class Decerealiser;
#include "CUdpServer.hpp"
#include "SClientFrame.hpp"
#include <mutex>


class CClientSocket: public CUdpObserver {
public:

    CClientSocket(int serverUdpPort, unsigned pilotIndex);

    SClientFrame GetFrame() const;
    void Run()  { mUdpServer.Run();  }
    void Stop() { mUdpServer.Stop(); }

private:

    CUdpServer mUdpServer;
    unsigned mPilotIndex;
    SClientFrame mFrame;
    mutable std::mutex mFrameMutex;

    virtual void UdpReceived(const boost::system::error_code& error,
                             std::size_t numBytes, const Array& bytes) override;
    void UpdateFrame(Decerealiser& cereal);
};


#endif
