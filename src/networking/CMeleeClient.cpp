#include "CMeleeClient.hpp"
#include "CGravOptions.hpp"

CMeleeClient::CMeleeClient(const CGravOptions& options, const CGravUpdateServer& updateServer):
    mUpdateServer(updateServer),
    mIsGameOver(),
    mGravMedia(options.GetMeleeOptions(),
               options.GetClientOptions().GetAllPilotOptions()),
    mGravScreen(mGravMedia.GetLevel().GetCanvas(), options.GetClientOptions(),
                mSong),
    mPowerups(mGravMedia.GetLevel(),
              options.GetMeleeOptions().GetPowerupRate()),
    mMeleeScore(mGravScreen.GetCanvas(),
                options.GetMeleeOptions().GetType(),
                mSong)
{

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
        std::lock_guard<std::mutex> lock{mGameOverMutex};
        if(mIsGameOver) break;
    }
}

void CMeleeClient::Stop() {
    std::lock_guard<std::mutex> lock{mGameOverMutex};
    mIsGameOver = true;
}
