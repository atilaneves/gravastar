#ifndef CMELEE_H
#define CMELEE_H


class CGravOptions;
class CPilot;
#include "CGravMedia.hpp"
#include "CGravScreen.hpp"
#include "CPowerups.hpp"
#include "CMeleeScore.hpp"
#include "CTimeCounter.hpp"
#include "CRandomSong.hpp"
#include "CMeleeServer.hpp"
#include <vector>


class CMelee {

public:

    enum { kMaxNbPilots = 4 };

    CMelee(const CGravOptions &options);
    virtual ~CMelee();

    void Run();


protected:

    pilots_t mPilots;

    CGravMedia   mGravMedia;
    CGravScreen  mGravScreen;
    CPowerups    mPowerups;
    CRandomSong  mSong;
    CMeleeScore  mMeleeScore;
    CTimeCounter mEndCounter;
    int          mWinner;
    CMeleeServer mServer;

    void    CheckGameOver();
    CPilot*  CreatePilot(const CGravOptions &options, int p);
    void     End(float avgFPS);
    pilots_t GetActivePilots() const;
    virtual int      GetWinner()  = 0;
    virtual bool     IsGameOver() = 0;
    void     Update(float dt);

};

#endif
