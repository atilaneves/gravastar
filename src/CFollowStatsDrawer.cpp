#include "CFollowStatsDrawer.hpp"
#include "CGravSprite.hpp"
#include "CTeam.hpp"
#include "CCanvas.hpp"
#include "CRectFill.hpp"
#include "CRect.hpp"
#include <cassert>


CFollowStatsDrawer::CFollowStatsDrawer(size_t spriteHash, uint8_t teamHash,
                                       float gauge, float maxGauge):
    mSpriteHash(spriteHash), mTeamHash(teamHash), mGauge(gauge), mMaxGauge(maxGauge) {

}

void CFollowStatsDrawer::Draw(CCanvas& canvas) const {
    const auto sprite = CGravSprite::GetSprite(mSpriteHash);
    assert(sprite);
    sprite->Draw(canvas, 0, 11);

    constexpr int kMaxSpecial = 10; //reference
    constexpr int kMaxWidth = 22;

    constexpr int outerRim = 2;
    constexpr int x0 = 37, y0 = 10; //where special bar starts
    const int w0 = int(kMaxWidth*(mMaxGauge/kMaxSpecial)) + outerRim;
    const int h0 = 5;

    const CRect rect(canvas, x0, y0, x0 + w0 - 1, y0 + h0 - 1,
                     CTeam::sWhite.GetMainColour());

    const int x1 = x0 + outerRim/2;
    const int y1 = y0 + outerRim/2;
    const int w1 = std::max(0, int(kMaxWidth * mGauge/kMaxSpecial));
    const int h1 = h0 - outerRim;

    if(w1) CRectFill(canvas, x1, y1, x1 + w1 - 1, y1 + h1 - 1,
                     CTeam::FromHash(mTeamHash).GetSecondaryColour());

}
