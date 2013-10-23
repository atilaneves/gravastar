#ifndef CCLIENT_SOCKET_HPP_
#define CCLIENT_SOCKET_HPP_

class Decerealiser;
#include "CUdpServer.hpp"
#include "SClientFrame.hpp"
#include <vector>
#include <tuple>
#include <mutex>
#include <stdint.h>
#include <boost/asio.hpp>


class CClientSocket: public CUdpServer {
public:

    CClientSocket(uint16_t serverUdpPort, unsigned pilotIndex);

    SClientFrame GetFrame() const;

private:

    unsigned mPilotIndex;
    SClientFrame mFrame;
    mutable std::mutex mFrameMutex;

    virtual void AfterReceive(const boost::system::error_code& error,
                              std::size_t numBytes, const Array& bytes) override;
    virtual void AfterSend(const boost::system::error_code& error,
                           std::size_t numBytes) override {}
    void UpdateFrame(Decerealiser& cereal);
};


#endif
