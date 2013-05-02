#include "CGravMedia.hpp"
#include "CMeleeOptions.hpp"


CGravMedia::CGravMedia(const CMeleeOptions &meleeOptions,
                       const CClientOptions::AllPilotOptions& allPilotOptions):
    mHashing(CGravSprite::EnableHashing(true)),
    mLevel(meleeOptions.GetLevelNb()),
    mShipYard(mLevel, allPilotOptions) {

    

}

CGravMedia::~CGravMedia() {
    CGravSprite::EnableHashing(false);
}
