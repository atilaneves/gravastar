#ifndef CMELEE_H
#define CMELEE_H


class CGravOptions;
class CPilotOptions;
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
    using pilots_t = CGravScreen::pilots_t;
    using Pilots = std::vector<CPilot*>;

    CMelee(const CGravOptions &options);
    virtual ~CMelee();

    void Run();


protected:

    Pilots mPilots;

    CMeleeServer mServer;
    CRandomSong  mSong;
    CGravMedia   mGravMedia;
    CGravScreen  mGravScreen;
    CPowerups    mPowerups;
    CMeleeScore  mMeleeScore;
    CTimeCounter mEndCounter;
    int          mWinner;

    void     CheckGameOver();
    CPilot*  CreatePilot(const CPilotOptions&, unsigned pilotIndex);
    void     End(float avgFPS);
    Pilots GetActivePilots() const;
    void     Update(float dt);

    virtual int  GetWinner()  = 0;
    virtual bool IsGameOver() = 0;
};

#endif
