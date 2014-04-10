#include "CLivesStats.hpp"
#include "CPilot.hpp"
#include "CCanvas.hpp"
#include "CTeam.hpp"
#include "CFont.hpp"
#include "CShipStatSprite.hpp"
#include "Cereal.hpp"
#include <string>
#include <cassert>


CLivesStats::CLivesStats(uint8_t teamHash, size_t spriteHash, uint8_t score):
    mTeamHash(teamHash), mSpriteHash(spriteHash), mScore(score) {

}


void CLivesStats::Draw(CCanvas& canvas) const {
    constexpr int x = 0, y = 1, dx = 10;
    const auto sprite = CGravSprite::GetSprite(mSpriteHash);
    assert(sprite);
    sprite->Draw(canvas, x, y);
    CFont font;
    const CTeam& team = CTeam::FromHash(mTeamHash);
    font.Print(canvas, x + dx, y, team.GetMainColour(), -1, "x");

    font.Print(canvas, x + 2*dx, y, team.GetMainColour(), -1,
               std::to_string(mScore));
}

void CLivesStats::cerealise(Cereal& cereal) {
    cereal.grain(mTeamHash);
    cereal.grain(mSpriteHash);
    cereal.grain(mScore);
}
