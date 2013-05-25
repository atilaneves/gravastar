#include "CMelee.hpp"
#include "CLevel.hpp"
#include "CKeyboard.hpp"
#include "CGravOptions.hpp"
#include "CGravScreen.hpp"
#include "CSpriteObjs.hpp"
#include "CShips.hpp"
#include "CProjectiles.hpp"
#include "CPilots.hpp"
#include "CPilotInputBot.hpp"
#include "CPilotFactory.hpp"
#include "CActionPicker.hpp"
#include "CMenuInputKey.hpp"
#include "CClock.hpp"
#include "CStats.hpp"


CMelee::CMelee(const CGravOptions &options):
    mServer(options),
    mGravMedia(options.GetMeleeOptions(),
               options.GetClientOptions().GetAllPilotOptions()),
    mGravScreen(mGravMedia.GetLevel().GetCanvas(), options.GetClientOptions(),
                mSong),
    mPowerups(mGravMedia.GetLevel(),
              options.GetMeleeOptions().GetPowerupRate()),
    mMeleeScore(mGravScreen.GetCanvas(),
                options.GetMeleeOptions().GetType(),
                mSong),
    mWinner(-1) {

    CKeyboard::Clear();
    CActionPicker::SetPowerups(&mPowerups);
    mSong.PlayLoop();

    for(const auto& pilotOptions: options.GetClientOptions().GetAllPilotOptions())
        mPilots.push_back(CreatePilot(pilotOptions));
}


CPilot* CMelee::CreatePilot(const CPilotOptions& pilotOptions) {
    const auto& shipYard = mGravMedia.GetShipYard();
    const auto& type     = pilotOptions.GetType();
    return CPilotFactory::Instance().CreateObject(type, pilotOptions,
                                                  shipYard, mMeleeScore);
}


CMelee::~CMelee() {
    mSong.Stop();
    for(unsigned int p = 0; p < mPilots.size(); p++) mPilots[p]->GameOver();
    CSpriteObjs::DeleteAll();
    CShips::RemoveAll();
    CProjectiles::RemoveAll();
    CPilot::ResetIndex();
    CPilots::RemoveAll();
    for(unsigned int p = 0; p < mPilots.size(); p++) delete mPilots[p];
}


void CMelee::Run() {
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


static CMelee::pilots_t getDisplayPilots(const CMelee::Pilots& pilots) {
    CMelee::pilots_t displayPilots;
    for(const auto& pilot: pilots) {
        displayPilots.push_back(pilot->MakeDisplayPilot());
    }
    return displayPilots;
}

void CMelee::Update(float dt) {
    auto pilots = GetActivePilots();
    for(unsigned int p = 0; p < pilots.size(); ++p) pilots[p]->CheckControls();
    CSpriteObjs::Update(dt);
    const auto displayPilots = getDisplayPilots(GetActivePilots());
    mServer.SendFrame(CSpriteObjs::Pack(displayPilots));
    mPowerups.Generate(dt);

    mGravScreen.Draw(displayPilots);
}


void CMelee::End(float avgFPS) {
    mServer.End();
    CKeyboard::Clear();
    printf("avg FPS: %.1f\n", avgFPS);
    if(mWinner >= 0) {
        CStats::AddWin(mWinner);
        mMeleeScore.Draw(mWinner, "WINNER!",
                         CPilots::GetPilot(mWinner).GetInput());
    }
    else mMeleeScore.Draw(mWinner, "DRAW", CPilotInputBot{});
}


auto CMelee::GetActivePilots() const -> Pilots {
    Pilots pilots;
    if(mWinner >= 0 && mPilots[mWinner]->IsAlive()) //winner gets display
        pilots.push_back(mPilots[mWinner]);
    else
        for(unsigned p = 0; p < mPilots.size(); ++p)
            if(mPilots[p]->IsAlive())
                pilots.push_back(mPilots[p]);
    return pilots;
}


void CMelee::CheckGameOver() {
    if(mWinner == -1 && IsGameOver() && !mEndCounter.IsActive()) { //game ended
        mEndCounter.Start(1.5); //seconds b4 it's over
        mWinner = GetWinner();
    }

    if(CMenuInputKey::sCancel.Pressed()) mEndCounter.Start(0.01);
}
