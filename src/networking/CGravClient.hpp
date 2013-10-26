#ifndef CGRAVCLIENT_H_
#define CGRAVCLIENT_H_

#include "CTcpClient.hpp"
#include "CGravOptions.hpp"
#include "CMeleeClient.hpp"
#include "CUdpReceiver.hpp"
#include "CClientSocket.hpp"
#include <deque>
#include <string>
#include <memory>

class CSongPlayer;
class CVersusMenu;

//Networking client class for connecting from the menu
class CGravClient: public CUdpObserver {
public:

    CGravClient(const std::string& addr, int port);

    void Run(CSongPlayer& songPlayer, CVersusMenu& versusMenu);

private:

    CTcpClient mTcpClient;
    CUdpReceiver mUdpReceiver;
    std::unique_ptr<CClientSocket> mClientSocket;
    std::unique_ptr<CMeleeClient> mMelee;

    void StartMeleeClient(CSongPlayer& songPlayer, std::deque<std::string> options,
                          const CClientOptions& vsClientOptions);
    void StopMeleeClient(int winner);
    CGravOptions GetGravOptions(std::deque<std::string>& options,
                                const CClientOptions& vsClientOptions) const;
    virtual void UdpReceived(const boost::system::error_code& error,
                             std::size_t numBytes, const Array& bytes) override;
};


#endif // CGRAVCLIENT_H_
