#include "CMeleeClient.hpp"
#include "CGravOptions.hpp"

CMeleeClient::CMeleeClient(const CGravOptions& options, const CGravUpdateServer& updateServer):
    mUpdateServer(updateServer),
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
    while(true) {
        for(const auto& spriteParams: oldSprites) {
            uint16_t hash, x, y;
            std::tie(hash, x, y) = spriteParams;
            const auto sprite = CGravSprite::GetSprite(hash);
            sprite->Erase(mGravMedia.GetLevel().GetCanvas(), x, y);
        }
        newSprites = mUpdateServer.GetSprites();
        for(const auto& spriteParams: newSprites) {
            uint16_t hash, x, y;
            std::tie(hash, x, y) = spriteParams;
            const auto sprite = CGravSprite::GetSprite(hash);
            assert(sprite);
            sprite->Draw(mGravMedia.GetLevel().GetCanvas(), x, y);
        }
        oldSprites = newSprites;
        mGravScreen.Draw(pilots_t{});
    }
}
