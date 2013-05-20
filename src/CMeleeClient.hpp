#ifndef CMELEE_CLIENT_HPP_
#define CMELEE_CLIENT_HPP_

class CGravOptions;
#include "CMelee.hpp"
#include "CGravUpdateServer.hpp"
#include "CGravMedia.hpp" //delete
#include "CGravScreen.hpp" //delete
#include "CRandomSong.hpp" //delete
#include <mutex>

class CMeleeClient { //TODO: public CMelee

public:

    using pilots_t = CGravScreen::pilots_t;

    CMeleeClient(const CGravOptions &options,
                 const CGravUpdateServer& updateServer);

    void Run();
    void Stop();

private:

    const CGravUpdateServer& mUpdateServer;
    bool mIsGameOver;
    std::mutex mGameOverMutex;

    //TODO: override
    //virtual int  GetWinner() override;
    //virtual bool IsGameOver() override { return mIsGameOver; }

    //TODO: delete
    CRandomSong  mSong;
    CGravMedia   mGravMedia;
    CGravScreen  mGravScreen;
    CPowerups    mPowerups;
    CMeleeScore  mMeleeScore;

};



#endif
