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
    CMeleeClientStarter(CRootMenu& rootMenu, const CClientMenu& menu);

    void Start(const std::vector<std::string>& options,
               const CClientOptions& vsClientOptions);
    void Stop();

private:

    CRootMenu& mRootMenu;
    const CClientMenu& mClientMenu;
    std::unique_ptr<CMeleeClient> mMelee;

    CGravOptions GetGravOptions(const std::vector<std::string>& options,
                                const CClientOptions& vsClientOptions) const;
};


#endif // CMELEECLIENTSTARTER_H
