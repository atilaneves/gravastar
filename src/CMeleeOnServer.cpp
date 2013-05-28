#include "CMeleeOnServer.hpp"
#include "CActionPicker.hpp"
#include "CGravOptions.hpp"
#include "CClock.hpp"
#include "CPilots.hpp"
#include "CPilot.hpp"
#include "CProjectiles.hpp"
#include "CPilotFactory.hpp"
#include "CSpriteObjs.hpp"
#include "CShips.hpp"


CMeleeOnServer::CMeleeOnServer(const CGravOptions &options):
    CMelee(options, new CMeleeServer(options)) {

    CActionPicker::SetPowerups(&mPowerups);

    const auto& allPilotOptions = options.GetClientOptions().GetAllPilotOptions();
    for(unsigned i = 0; i < allPilotOptions.size(); ++i)
        mPilots.push_back(CreatePilot(allPilotOptions[i], i));
}

CMeleeOnServer::~CMeleeOnServer() {
    mSong.Stop();
    for(unsigned int p = 0; p < mPilots.size(); p++) mPilots[p]->GameOver();
    CSpriteObjs::DeleteAll();
    CShips::RemoveAll();
    CProjectiles::RemoveAll();
    CPilot::ResetIndex();
    CPilots::RemoveAll();
    for(unsigned int p = 0; p < mPilots.size(); p++) delete mPilots[p];
}


CPilot* CMeleeOnServer::CreatePilot(const CPilotOptions& pilotOptions, unsigned pilotIndex) {
    const auto& shipYard = mGravMedia.GetShipYard();
    const auto& type     = mServer->GetPilotType(pilotOptions.GetType(), pilotIndex);
    return CPilotFactory::Instance().CreateObject(type, pilotOptions,
                                                  shipYard, mMeleeScore);
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
    mServer->SendFrame(CSpriteObjs::Pack(displayPilots));
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
