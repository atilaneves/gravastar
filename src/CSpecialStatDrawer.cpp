#include "CSpecialStatDrawer.hpp"
#include "CProjSpecial.hpp"
#include "CFollowSpecial.hpp"
#include "CFollowStatsDrawer.hpp"
#include "CProjStatDrawer.hpp"
#include <cassert>

CSpecialStatDrawer::CSpecialStatDrawer(uint8_t specialHash, size_t spriteHash, uint8_t teamHash,
                                       float gauge, float maxGauge):
    mSpecialHash(specialHash), mSpriteHash(spriteHash), mTeamHash(teamHash),
    mGauge(gauge), mMaxGauge(maxGauge) {
}

void CSpecialStatDrawer::Draw(CCanvas& canvas) const {
    if(mSpecialHash == CProjSpecial::CLASS_HASH)
        CProjStatDrawer(mSpriteHash, mTeamHash, mGauge, mMaxGauge).Draw(canvas);
    else if(mSpecialHash == CFollowSpecial::CLASS_HASH)
        CFollowStatsDrawer(mSpriteHash, mTeamHash, mGauge, mMaxGauge).Draw(canvas);
    else
        assert(false);
}
