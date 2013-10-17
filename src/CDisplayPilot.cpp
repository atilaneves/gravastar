#include "CDisplayPilot.hpp"
#include "Cereal.hpp"


CDisplayPilot::CDisplayPilot(uint8_t index,
                             const CScreenPos& pos, const CVector2& vel,
                             const CTeam& team, uint8_t score,
                             CPilotStats* stats, bool isAlive,
                             bool hasSplitScreen):
    mIndex(index),mPosition(pos.GetX(), pos.GetY()),
    mVelocity(vel.GetX(), vel.GetY()),
    mTeam(team.GetHash()), mScore(score), mStats(stats),
    mIsAlive(isAlive), mHasSplitScreen(hasSplitScreen) {
}


void CDisplayPilot::cerealise(Cereal& cereal) {
    cereal.grain(mPosition.x);
    cereal.grain(mPosition.y);
    cereal.grain(mVelocity.x);
    cereal.grain(mVelocity.y);
    cereal.grain(mTeam);
    cereal.grain(mScore);
    cereal.grain(mIsAlive);
}

void CDisplayPilot::DrawStats(CCanvas& canvas) const {
    if(mStats) {
        mStats->Draw(canvas);
    }
}
