#ifndef CGRAV_UPDATE_SERVER_HPP_
#define CGRAV_UPDATE_SERVER_HPP_

#include "CUdpServer.hpp"
#include "SClientFrame.hpp"
#include <vector>
#include <tuple>
#include <mutex>
#include <stdint.h>
#include <boost/asio.hpp>


class CGravUpdateServer: public CUdpServer {
public:

    using Sprites = SClientFrame::Sprites;
    using Pilots = SClientFrame::Pilots;

    CGravUpdateServer();
    Pilots GetPilots() const;
    Sprites GetSprites() const;

private:

    SClientFrame mFrame;
    mutable std::mutex mFrameMutex;

    virtual void AfterReceive(const boost::system::error_code& error,
                              std::size_t numBytes, const Array& bytes) override;
    virtual void AfterSend(const boost::system::error_code& error,
                           std::size_t numBytes) override;
};


#endif
