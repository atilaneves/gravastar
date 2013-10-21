#include "CSpecialStatDrawer.hpp"
#include "CProjSpecial.hpp"
#include "CFollowSpecial.hpp"
#include "CFollowStatsDrawer.hpp"
#include "CProjStatDrawer.hpp"
#include "Cereal.hpp"
#include <cassert>

CSpecialStatDrawer::CSpecialStatDrawer(uint8_t specialHash, size_t spriteHash, uint8_t teamHash,
                                       uint8_t gauge, uint8_t maxGauge):
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

void CSpecialStatDrawer::cerealise(Cereal& cereal) {
    cereal.grain(mSpecialHash);
    cereal.grain(mSpriteHash);
    cereal.grain(mTeamHash);
    cereal.grain(mGauge);
    cereal.grain(mMaxGauge);
}
