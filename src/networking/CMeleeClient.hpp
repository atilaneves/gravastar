#ifndef CMELEE_CLIENT_HPP_
#define CMELEE_CLIENT_HPP_

class CGravOptions;
class CClientSocket;
#include "CMelee.hpp"
#include <atomic>


class CMeleeClient: public CMelee {

public:

    CMeleeClient(const CGravOptions &options,
                 CClientSocket& clientSocket);

    virtual void Run() override;
    void Stop(int winner);

private:

    CClientSocket& mClientSocket;
    std::atomic_bool mIsGameOver;

    virtual int  GetWinner()  override { return mWinner;     }
    virtual bool IsGameOver() override { return mIsGameOver; }
};



#endif
