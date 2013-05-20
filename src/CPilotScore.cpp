#include "CPilotScore.hpp"
#include "CFont.hpp"
#include "CPilots.hpp"
#include "CPilot.hpp"
#include "CShipStatSprite.hpp"
#include "CTeam.hpp"
#include "CStats.hpp"
#include <stdio.h>


CPilotScore::CPilotScore(int index):
    mIndex(index) {

}


void CPilotScore::Draw(const CFont &font, CCanvas &canvas,int x,int y) const {

    const CTeam &team = mIndex >= 0 ? CPilots::GetPilot(mIndex).GetTeam():
        CTeam::sWhite;
    int col = team.GetMainColour();
    char scoreString[200];
    sprintf(scoreString, "  %s: %d (W%d K%d)",
            CPilots::GetPilot(mIndex).GetName().c_str(),
            CPilots::GetPilot(mIndex).GetScore(),
            CStats::GetNbWins(mIndex), CStats::GetNbFrags(mIndex));

    y += 5 + (mIndex + 1) * (font.GetHeight()*3)/2;
    font.Print(canvas, x, y, col, -1, scoreString);
    CPilots::GetPilot(mIndex).GetShipStatSprite().Draw(canvas, x, y);
}


int CPilotScore::GetScore() const {
    return CPilots::GetPilot(mIndex).GetScore();
}


bool CPilotScore::operator>(const CPilotScore &pilotScore) const {
    return GetScore() > pilotScore.GetScore();
}
