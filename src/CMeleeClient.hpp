#ifndef CMELEE_CLIENT_HPP_
#define CMELEE_CLIENT_HPP_

class CGravOptions;
#include "CMelee.hpp"
#include "CGravUpdateServer.hpp"
#include "CGravMedia.hpp" //delete
#include "CGravScreen.hpp" //delete
#include "CRandomSong.hpp" //delete

class CMeleeClient { //TODO: public CMelee

public:

    CMeleeClient(const CGravOptions &options,
                 const CGravUpdateServer& updateServer);

    void Run();

private:

    const CGravUpdateServer& mUpdateServer;

    //TODO: override
    //virtual int  GetWinner() override;
    //virtual bool IsGameOver() override;

    //TODO: delete
    CRandomSong  mSong;
    CGravMedia   mGravMedia;
    CGravScreen  mGravScreen;
    CPowerups    mPowerups;
    CMeleeScore  mMeleeScore;

};



#endif
