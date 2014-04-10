#include "CDisplayPilot.hpp"
#include "Cereal.hpp"

CDisplayPilot::CDisplayPilot(uint8_t index, const CScreenPos &pos,
                             const CVector2 &vel, uint8_t teamHash,
                             uint8_t score, CPilotStats stats, bool isAlive,
                             bool hasSplitScreen)
    : mIndex(index), mPosition(pos.GetX(), pos.GetY()),
      mVelocity(vel.GetX(), vel.GetY()), mTeamHash(teamHash), mScore(score),
      mStats(std::move(stats)), mIsAlive(isAlive),
      mHasSplitScreen(hasSplitScreen) {}

void CDisplayPilot::cerealise(Cereal& cereal) {
    cereal.grain(mPosition.x);
    cereal.grain(mPosition.y);
    cereal.grain(mVelocity.x);
    cereal.grain(mVelocity.y);
    cereal.grain(mTeamHash);
    cereal.grain(mScore);
    cereal.grain(mStats);
    cereal.grain(mIsAlive);
}

void CDisplayPilot::DrawStats(CCanvas& canvas) const {
    mStats.Draw(canvas);
}
