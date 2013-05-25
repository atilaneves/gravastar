#ifndef CGRAV_UPDATE_SERVER_HPP_
#define CGRAV_UPDATE_SERVER_HPP_

#include "CUdpServer.hpp"
#include "CFramePacker.hpp"
#include <vector>
#include <tuple>
#include <mutex>
#include <stdint.h>
#include <boost/asio.hpp>


class CGravUpdateServer: public CUdpServer {
public:

    using Sprites = std::vector<std::tuple<uint16_t, uint16_t, uint16_t>>;
    using Pilots = CFramePacker::Pilots;

    CGravUpdateServer();
    Pilots GetPilots() const;
    Sprites GetSprites() const;

private:

    Pilots mPilots;
    Sprites mSprites;
    mutable std::mutex mSpriteMutex;
    mutable std::mutex mPilotMutex;

    virtual void AfterReceive(const boost::system::error_code& error,
                              std::size_t numBytes, const Array& bytes) override;
    virtual void AfterSend(const boost::system::error_code& error,
                           std::size_t numBytes) override;
};


#endif
