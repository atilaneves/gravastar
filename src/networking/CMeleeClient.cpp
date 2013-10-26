#include "CMeleeClient.hpp"
#include "CGravOptions.hpp"
#include "CClientSocket.hpp"
#include "CPilot.hpp"
#include <iostream>

using namespace std;


CMeleeClient::CMeleeClient(const CGravOptions& options,
                           CClientSocket& clientSocket):
    CMelee(options, nullptr), /*nullptr: no server*/
    mClientSocket(clientSocket),
    mIsGameOver() {

}

void CMeleeClient::Run() {
    while(!mClientSocket.IsReady()) ; //wait for server

    SClientFrame::Sprites oldSprites, newSprites;
    while(!mIsGameOver) {

        for(const auto& p: mPilots) p->CheckControls(&mClientSocket);

        for(const auto& levelSprite: oldSprites) {
            const auto sprite = CGravSprite::GetSprite(levelSprite.GetHash());
            assert(sprite);
            sprite->Erase(mGravMedia.GetLevel().GetCanvas(),
                          levelSprite.GetX(), levelSprite.GetY());
        }

        const auto frame = mClientSocket.GetFrame();
        newSprites = frame.sprites;
        for(const auto& levelSprite: newSprites) {
            const auto sprite = CGravSprite::GetSprite(levelSprite.GetHash());
            if(!sprite) {
                cerr << "Unknown sprite hash "<< levelSprite.GetHash() << endl;
            }
            assert(sprite);
            sprite->Draw(mGravMedia.GetLevel().GetCanvas(),
                          levelSprite.GetX(), levelSprite.GetY());
        }
        oldSprites = newSprites;
        const auto pilots = frame.pilots;
        assert(pilots.size() <= mPilots.size()); //server pilots could have died
        for(size_t i = 0; i < pilots.size(); ++i)
            mPilots[i]->SetScore(pilots[i].GetScore());

        mGravScreen.Draw(pilots);
    }

    End(0.0f /*avgFPS*/);
}

void CMeleeClient::Stop(int winner) {
    mIsGameOver = true;
    mWinner = winner;
}
