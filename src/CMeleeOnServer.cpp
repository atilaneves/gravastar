#include "CMeleeOnServer.hpp"
#include "CActionPicker.hpp"
#include "CGravOptions.hpp"
#include "CClock.hpp"
#include "CPilot.hpp"
#include "CSpriteObjs.hpp"


CMeleeOnServer::CMeleeOnServer(const CGravOptions &options):
    CMelee(options, new CServerSocket(options)) {

    CActionPicker::SetPowerups(&mPowerups);
}



static CMeleeOnServer::pilots_t getDisplayPilots(const CMeleeOnServer::Pilots& pilots) {
    CMeleeOnServer::pilots_t displayPilots;
    for(const auto& pilot: pilots) {
        displayPilots.push_back(pilot->MakeDisplayPilot());
    }
    return displayPilots;
}


void CMeleeOnServer::Run() {
    CClock::Reset();
    float maxDt = 0.05, dt = 0, totalTime = 0;
    int nbFrames = 0;

    while(!mEndCounter.JustFinished()) {
        CSpriteObjs::Erase();
        Update(dt);
        dt = CClock::DeltaS();
        totalTime += dt;
        nbFrames++;
        if(dt > maxDt) dt = maxDt; //no big updates
        CheckGameOver();
        mSong.Poll();
    }

    End(nbFrames / totalTime);
}

void CMeleeOnServer::Update(float dt) {
    auto pilots = GetActivePilots();
    for(unsigned int p = 0; p < pilots.size(); ++p) pilots[p]->CheckControls();
    CSpriteObjs::Update(dt);
    const auto displayPilots = getDisplayPilots(GetActivePilots());
    mServerSocket->SendFrame(CSpriteObjs::Pack(displayPilots));
    mPowerups.Generate(dt);

    mGravScreen.Draw(displayPilots);
}


auto CMeleeOnServer::GetActivePilots() const -> Pilots {
    Pilots pilots;
    if(mWinner >= 0 && mPilots[mWinner]->IsAlive()) //winner gets display
        pilots.push_back(mPilots[mWinner]);
    else
        for(unsigned p = 0; p < mPilots.size(); ++p)
            if(mPilots[p]->IsAlive())
                pilots.push_back(mPilots[p]);
    return pilots;
}
