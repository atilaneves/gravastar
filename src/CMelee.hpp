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
#include "CServerSocket.hpp"
#include "CRandomSong.hpp"
#include <string>
#include <vector>
#include <memory>
#include <atomic>


class CMelee {

public:

    enum { kMaxNbPilots = 4 };
    using Pilots = std::vector<std::shared_ptr<CPilot>>;

    CMelee(const CGravOptions &options, CServerSocket* serverSocket = nullptr);
    virtual ~CMelee();

    virtual void Run() = 0;


private:

    virtual int  GetWinner()  = 0;
    virtual bool IsGameOver() = 0;
    CPilot* CreatePilot(const CPilotOptions&, unsigned pilotIndex);
    std::string GetRealPilotType(const std::string& type, unsigned pilotIndex) const;

protected:

    std::unique_ptr<CServerSocket> mServerSocket;
    CRandomSong  mSong;
    CGravMedia   mGravMedia;
    CGravScreen  mGravScreen;
    CPowerups    mPowerups;
    CMeleeScore  mMeleeScore;
    CTimeCounter mEndCounter;
    std::atomic_int mWinner;
    Pilots mPilots;

    void CheckGameOver();
    void End(float avgFPS);

};

#endif
