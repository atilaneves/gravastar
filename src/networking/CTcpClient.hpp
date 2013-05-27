#ifndef CTCPCLIENT_H
#define CTCPCLIENT_H

#include <string>
#include <functional>
#include <vector>
#include <mutex>
#include <atomic>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using boost::asio::ip::address_v4;


class CTcpClient {
public:

    using MsgBuf = std::array<unsigned char, 1024>;
    using MsgHandler = std::function<void(const MsgBuf&, size_t)>;

    CTcpClient(const std::string& addr, int port);
    void BlockingConnect(double seconds=0);
    bool Connect();
    bool ReadUntil(std::atomic_bool& condition, const MsgHandler& msgHandler);
    void Stop() { std::lock_guard<std::mutex> lock{mStopMutex}; mStop = true; }
    void Send(const std::vector<unsigned char>& bytes);

private:

    mutable std::mutex mStopMutex;
    bool mStop;
    boost::asio::io_service mIoService;
    tcp::socket mSocket;
    const address_v4 mServerAddress;
    const int mServerPort;
    tcp::endpoint mEndpoint;
};


#endif // CTCPCLIENT_H
