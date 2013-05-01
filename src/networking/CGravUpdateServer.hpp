#ifndef CGRAV_UPDATE_SERVER_HPP_
#define CGRAV_UPDATE_SERVER_HPP_

#include "CUdpServer.hpp"
#include <functional>
#include <boost/asio.hpp>


class CGravUpdateServer: public CUdpServer {
public:

    CGravUpdateServer();

private:

    virtual void AfterReceive(const boost::system::error_code& error,
                              std::size_t numBytes, const Array& bytes) override;
    virtual void AfterSend(const boost::system::error_code& error,
                           std::size_t numBytes) override;
};


#endif
