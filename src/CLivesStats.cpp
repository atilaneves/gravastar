#include "CLivesStats.hpp"
#include "CPilot.hpp"
#include "CCanvas.hpp"
#include "CTeam.hpp"
#include "CFont.hpp"
#include "CShipStatSprite.hpp"
#include <string>


void CLivesStats::Draw(CCanvas& canvas) const {

    constexpr int x = 0, y = 1, dx = 10;
    mStatSprite.Draw(canvas, x, y);
    CFont font;
    font.Print(canvas, x + dx, y, mTeam.GetMainColour(), -1, "x");

    font.Print(canvas, x + 2*dx, y, mTeam.GetMainColour(), -1,
               std::to_string(mScore));
}
