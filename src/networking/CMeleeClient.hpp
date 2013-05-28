#ifndef CMELEE_CLIENT_HPP_
#define CMELEE_CLIENT_HPP_

class CGravOptions;
class CGravUpdateServer;
#include "CMelee.hpp"
#include <atomic>


class CMeleeClient: public CMelee {

public:

    using pilots_t = CGravScreen::pilots_t;

    CMeleeClient(const CGravOptions &options,
                 const CGravUpdateServer& updateServer);

    virtual void Run() override;
    void Stop() { mIsGameOver = true; }
    void SetWinner(int winner) { mWinner = winner; }

private:

    const CGravUpdateServer& mUpdateServer;
    std::atomic_bool mIsGameOver;
    std::atomic_int mWinner;

    virtual int  GetWinner()  override { return mWinner;     }
    virtual bool IsGameOver() override { return mIsGameOver; }
};



#endif
