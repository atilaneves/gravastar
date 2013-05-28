#ifndef CMELEECLIENTSTARTER_H
#define CMELEECLIENTSTARTER_H


class CRootMenu;
class CClientMenu;
class CClientOptions;
#include "CGravOptions.hpp"
#include "CMeleeClient.hpp"
#include <vector>
#include <string>
#include <memory>


class CMeleeClientStarter {
public:
    CMeleeClientStarter(CRootMenu& rootMenu, const CClientMenu& menu,
                        uint16_t serverUdpPort);

    void Start(std::deque<std::string> options,
               const CClientOptions& vsClientOptions);
    void Stop(int winner);

private:

    CRootMenu& mRootMenu;
    const CClientMenu& mClientMenu;
    uint16_t mServerUdpPort;
    std::unique_ptr<CMeleeClient> mMelee;

    CGravOptions GetGravOptions(std::deque<std::string>& options,
                                const CClientOptions& vsClientOptions) const;
};


#endif // CMELEECLIENTSTARTER_H
