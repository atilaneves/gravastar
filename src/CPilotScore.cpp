#include "CPilotScore.hpp"
#include "CFont.hpp"
#include "CPilots.hpp"
#include "CPilot.hpp"
#include "CShipStatSprite.hpp"
#include "CTeam.hpp"
#include "CStats.hpp"
#include <sstream>

using namespace std;

CPilotScore::CPilotScore(int index):
    mIndex(index) {

}


void CPilotScore::Draw(const CFont &font, CCanvas &canvas, int x, int y) const {

    const CTeam &team = mIndex >= 0 ? CPilots::GetPilot(mIndex).GetTeam():
        CTeam::sWhite;
    int col = team.GetMainColour();
    const auto& pilot = CPilots::GetPilot(mIndex);
    stringstream score;
    score << "  " << pilot.GetName() << ": " << pilot.GetScore() <<
        " (W" << CStats::GetNbWins(mIndex) <<
        " K" << CStats::GetNbFrags(mIndex) << ")";
    y += 5 + (mIndex + 1) * (font.GetHeight() * 3) / 2;
    font.Print(canvas, x, y, col, -1, score.str());
    CPilots::GetPilot(mIndex).GetShipStatSprite().Draw(canvas, x, y);
}


int CPilotScore::GetScore() const {
    return CPilots::GetPilot(mIndex).GetScore();
}


bool CPilotScore::operator>(const CPilotScore &pilotScore) const {
    return GetScore() > pilotScore.GetScore();
}
