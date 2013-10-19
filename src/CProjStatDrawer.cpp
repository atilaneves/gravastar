#include "CProjStatDrawer.hpp"
#include "CGravSprite.hpp"
#include "CFont.hpp"
#include <cassert>


CProjStatDrawer::CProjStatDrawer(size_t spriteHash, uint8_t teamHash, float gauge, float maxGauge):
    mSpriteHash(spriteHash), mTeamHash(teamHash), mGauge(gauge) {


}


void CProjStatDrawer::Draw(CCanvas& canvas) const {
    const auto sprite = CGravSprite::GetSprite(mSpriteHash);
    assert(sprite);
    sprite->Draw(canvas, 0, 11);

    const int col = CTeam::FromHash(mTeamHash).GetMainColour();
    constexpr int x = 0, y = 11, dx = 10;
    const CFont font;
    font.Print(canvas, x + dx, y, col, -1, "x");
    font.Print(canvas, x + 2*dx, y, col, -1,
               std::to_string(static_cast<int>(mGauge)));
}
