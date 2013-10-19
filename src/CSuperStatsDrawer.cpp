#include "CSuperStatsDrawer.hpp"
#include "CGravSprite.hpp"
#include <cassert>


CSuperStatsDrawer::CSuperStatsDrawer(bool canUse, size_t spriteHash):
    mCanUse(canUse), mSpriteHash(spriteHash) {
}


void CSuperStatsDrawer::Draw(CCanvas& canvas) const {
    if(!mCanUse) return;
    const auto sprite = CGravSprite::GetSprite(mSpriteHash);
    assert(sprite);
    constexpr int x = 67, y = 10;
    sprite->Draw(canvas, x, y);
}
