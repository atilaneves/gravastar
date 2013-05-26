#include "CLivesStats.hpp"
#include "CPilot.hpp"
#include "CCanvas.hpp"
#include "CTeam.hpp"
#include "CFont.hpp"
#include "CShipStatSprite.hpp"
#include <stdio.h>


void CLivesStats::Draw() {

    constexpr int x = 0, y = 1, dx = 10;
    mStatSprite->Draw(mCanvas, x, y);
    CFont font;
    font.Print(mCanvas, x + dx, y, mPilot.GetTeam().GetMainColour(), -1, "x");

    char score[100];
    sprintf(score, "%d", (int)mPilot.GetScore());
    font.Print(mCanvas, x + 2*dx, y, mPilot.GetTeam().GetMainColour(), -1, score);
}
