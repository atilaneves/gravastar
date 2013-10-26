#include "CMelee.hpp"
#include "CLevel.hpp"
#include "CKeyboard.hpp"
#include "CGravOptions.hpp"
#include "CGravScreen.hpp"
#include "CPilots.hpp"
#include "CPilotInputBot.hpp"
#include "CPilotFactory.hpp"
#include "CMenuInputKey.hpp"
#include "CStats.hpp"
#include "CPilots.hpp"
#include "CProjectiles.hpp"
#include "CPilotFactory.hpp"
#include "CSpriteObjs.hpp"
#include "CShips.hpp"


CMelee::CMelee(const CGravOptions &options,
               CServerSocket* serverSocket):
    mServerSocket(serverSocket),
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
    mSong.PlayLoop();

    const auto& allPilotOptions = options.GetClientOptions().GetAllPilotOptions();
    for(unsigned i = 0; i < allPilotOptions.size(); ++i)
        mPilots.emplace_back(CreatePilot(allPilotOptions[i], i));
}

CMelee::~CMelee() {
    mSong.Stop();
    for(unsigned int p = 0; p < mPilots.size(); p++) mPilots[p]->GameOver();
    CSpriteObjs::DeleteAll();
    CShips::RemoveAll();
    CProjectiles::RemoveAll();
    CPilot::ResetIndex();
    CPilots::RemoveAll();
}

CPilot* CMelee::CreatePilot(const CPilotOptions& pilotOptions, unsigned pilotIndex) {
    const auto& shipYard   = mGravMedia.GetShipYard();
    const auto& optionType = pilotOptions.GetType();
    const auto& realType   = mServerSocket ?
                             mServerSocket->GetPilotType(optionType, pilotIndex) :
                             optionType;
    std::cout << "real type: " << realType << std::endl;

    return CPilotFactory::Instance().CreateObject(realType, pilotOptions,
                                                  shipYard, mMeleeScore);
}


void CMelee::End(float avgFPS) {
    if(mServerSocket) mServerSocket->End(mWinner);
    CKeyboard::Clear();
    if(mWinner >= 0) {
        CStats::AddWin(mWinner);
        mMeleeScore.Draw(mWinner, "WINNER!",
                         CPilots::GetPilot(mWinner).GetInput());
    }
    else mMeleeScore.Draw(mWinner, "DRAW", CPilotInputBot{});
}



void CMelee::CheckGameOver() {
    if(mWinner == -1 && IsGameOver() && !mEndCounter.IsActive()) { //game ended
        mEndCounter.Start(1.5); //seconds b4 it's over
        mWinner = GetWinner();
    }

    if(CMenuInputKey::sCancel.Pressed()) mEndCounter.Start(0.01);
}
