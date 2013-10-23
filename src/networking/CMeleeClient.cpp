#include "CMeleeClient.hpp"
#include "CGravOptions.hpp"
#include "CClientSocket.hpp"
#include "CPilot.hpp"
#include <iostream>

using namespace std;


CMeleeClient::CMeleeClient(const CGravOptions& options,
                           const CClientSocket& clientSocket):
    CMelee(options, nullptr), /*nullptr: no server*/
    mClientSocket(clientSocket),
    mIsGameOver() {

}

void CMeleeClient::Run() {
    SClientFrame::Sprites oldSprites, newSprites;
    for(;;) {
        for(const auto& levelSprite: oldSprites) {
            const auto sprite = CGravSprite::GetSprite(levelSprite.GetHash());
            assert(sprite);
            sprite->Erase(mGravMedia.GetLevel().GetCanvas(),
                          levelSprite.GetX(), levelSprite.GetY());
        }

        //TODO: find out why I can just get the frame here and use it
        newSprites = mClientSocket.GetFrame().sprites;
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
        const auto pilots = mClientSocket.GetFrame().pilots;
        assert(pilots.size() <= mPilots.size()); //server pilots could have died
        for(size_t i = 0; i < pilots.size(); ++i)
            mPilots[i]->SetScore(pilots[i].GetScore());

        mGravScreen.Draw(pilots);
        if(mIsGameOver) break;
    }
    const auto avgFPS = 0.0f;
    End(avgFPS);
}

void CMeleeClient::Stop(int winner) {
    mIsGameOver = true;
    mWinner = winner;
}
