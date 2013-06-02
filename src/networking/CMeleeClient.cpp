#include "CMeleeClient.hpp"
#include "CGravOptions.hpp"
#include "CGravUpdateServer.hpp"


CMeleeClient::CMeleeClient(const CGravOptions& options,
                           const CGravUpdateServer& updateServer):
    CMelee(options, nullptr), /*nullptr: no server*/
    mUpdateServer(updateServer),
    mIsGameOver() {

}

void CMeleeClient::Run() {
    CGravUpdateServer::Sprites oldSprites, newSprites;
    for(;;) {
        for(const auto& levelSprite: oldSprites) {
            const auto sprite = CGravSprite::GetSprite(levelSprite.GetHash());
            assert(sprite);
            sprite->Erase(mGravMedia.GetLevel().GetCanvas(),
                          levelSprite.GetX(), levelSprite.GetY());
        }
        newSprites = mUpdateServer.GetSprites();
        for(const auto& levelSprite: newSprites) {
            const auto sprite = CGravSprite::GetSprite(levelSprite.GetHash());
            assert(sprite);
            sprite->Draw(mGravMedia.GetLevel().GetCanvas(),
                          levelSprite.GetX(), levelSprite.GetY());
        }
        oldSprites = newSprites;
        mGravScreen.Draw(mUpdateServer.GetPilots());
        if(mIsGameOver) break;
    }
    const auto avgFPS = 0.0f;
    End(avgFPS);
}

void CMeleeClient::Stop(int winner) {
    mIsGameOver = true;
    mWinner = winner;
}
