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


CMelee::CMelee(const CGravOptions &options,
               CMeleeServer* server):
    mServer(server),
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
}



void CMelee::End(float avgFPS) {
    if(mServer) mServer->End();
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
