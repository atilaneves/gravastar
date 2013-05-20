#include "CMeleeScore.hpp"
#include "CFont.hpp"
#include "CSound.hpp"
#include "CCanvas.hpp"
#include "CPilot.hpp"
#include "CTeam.hpp"
#include "CPilots.hpp"
#include "CResolution.hpp"
#include "CMenuInputKey.hpp"
#include "CClockTimer.hpp"
#include "CPilotInput.hpp"
#include "CColour.hpp"
#include "CRectFill.hpp"
#include "CRect.hpp"
#include "CKeyboard.hpp"
#include "CSong.hpp"
#include "fontsdat.h"
#include <stdio.h>
#include <algorithm>


CMeleeScore::CMeleeScore(CCanvas &canvas, const std::string& meleeType,
                         CSong& song):
    mCanvas(canvas), mSong(song), mMeleeType(meleeType),
    mFont(EmpireBuilderDocument9) {
    mSounds["Blue"]   = new CSound("victory0");
    mSounds["Red"]    = new CSound("victory1");
    mSounds["Green"]  = new CSound("victory2");
    mSounds["Yellow"] = new CSound("victory3");
    mSounds["White"]  = new CSound("draw");
    }


CMeleeScore::~CMeleeScore() {
    for(soundPlace_t i = mSounds.begin(); i != mSounds.end(); ++i)
        delete (*i).second;
}


void CMeleeScore::Draw(int winner, const std::string& title,
                       const CPilotInput &input) {

    std::vector<CPilotScore> scores = GetScores();
    int x = CResolution::GetWidth()  / 2 - CResolution::GetWidth() / 6;
    int y = CResolution::GetHeight() / 2 - CResolution::GetHeight() / 12;
    const CTeam &team = winner >=0 ? CPilots::GetPilot(winner).GetTeam() :
        CTeam::sWhite;
    int colour = team.GetMainColour();
    DrawGeometry(x, y, colour);

    for(unsigned int p = 0; p < scores.size(); p++)
        scores[p].Draw(mFont, mCanvas, x, y);

    mFont.Print(mCanvas, x, y, colour, -1, title);
    mCanvas.Flip();
    if(title != "Pause") PlaySound(team);
    End(input);
}


std::vector<CPilotScore> CMeleeScore::GetScores() const {
    std::vector<CPilotScore> scores;
    for(int p=0; p<CPilots::GetNbPilots(); p++) scores.push_back(CPilotScore(p));
    std::stable_sort(scores.begin(), scores.end(),
                     [](const CPilotScore &ps1, const CPilotScore &ps2) {
                         return ps1 > ps2;
                     });
    return scores;
}



void CMeleeScore::End(const CPilotInput &input) const {
    CClockTimer::Instance().Pause();
    while(input.Start()) ; //wait til finger off
    while(!input.Start() && !CMenuInputKey::sCancel.Pressed()) mSong.Poll();
    CKeyboard::Clear();
    while(CMenuInputKey::sCancel.Pressed()) mSong.Poll();
    CClockTimer::Instance().Unpause();
}


void CMeleeScore::DrawGeometry(int x, int y, int col) const {
    x -= 10;
    y -= 10;
    int width  = 240;
    int height = 120;
    CRectFill(mCanvas, x, y, x+width, y+height, CColour::GetBlack());
    CRect(mCanvas, x, y, x+width, y+height, col);
}


void CMeleeScore::PlaySound(const CTeam &team) {
    mSounds[team.GetName()]->PlayCentre();
}
