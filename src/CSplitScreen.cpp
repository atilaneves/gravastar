#include "CSplitScreen.hpp"
#include "CScreenPos.hpp"
#include "CVector2.hpp"
#include "CCanvas.hpp"
#include "CPilot.hpp"
#include "CShip.hpp"
#include "CRect.hpp"
#include "CTeam.hpp"
#include <algorithm>
#include <assert.h>


CSplitScreen::CSplitScreen(const CCanvas &levelCanvas, CCanvas &drawCanvas,
                           int width, int height,
                           int drawX, int drawY):
    mStatsCanvas(kStatsCanvasWidth, kStatsCanvasHeight),
    mSubCanvas(drawCanvas, drawX, drawY, width, height),
    mLevelCanvas(&levelCanvas) {

}


CSplitScreen::CSplitScreen(const CSplitScreen &split):
    mStatsCanvas(kStatsCanvasWidth, kStatsCanvasHeight),
    mSubCanvas(split.mSubCanvas),
    mLevelCanvas(split.mLevelCanvas) {
}


void CSplitScreen::DrawRadar(const DisplayPilots& pilots, const DisplayPilots& humans) {
    mRadar.Draw(mSubCanvas, mSubCanvas.GetWidth() - 30, 5, pilots, humans,
                GetCentre(humans));
}


void CSplitScreen::Grab(const DisplayPilots& pilots) {
    int flipX = mLevelCanvas->GetWidth() < mSubCanvas.GetWidth() ?
        mSubCanvas.GetWidth() / 2 - mLevelCanvas->GetWidth() / 2 - 1: 0;
    int flipY = mLevelCanvas->GetHeight() < mSubCanvas.GetHeight() ?
        mSubCanvas.GetHeight() / 2 - mLevelCanvas->GetHeight() / 2 - 1 : 0;
    int width  = std::min(mSubCanvas.GetWidth(),  mLevelCanvas->GetWidth());
    int height = std::min(mSubCanvas.GetHeight(), mLevelCanvas->GetHeight());
    CScreenPos pos = GetGrabPos(pilots);
    mLevelCanvas->Blit(mSubCanvas, pos.GetX(), pos.GetY(), flipX, flipY,
                       width, height);

    const CTeam &team = pilots.size() == 1 ? pilots[0].GetTeam() : CTeam::sWhite;
    CRect rect(mSubCanvas, flipX, flipY, flipX + width - 1,
               flipY + height - 1, team.GetMainColour());
    for(unsigned int p = 0; p < pilots.size(); p++)
        DrawStats(pilots[p], 2, 2 + p*25);
}


void CSplitScreen::DrawStats(const CDisplayPilot& pilot, int x, int y) {
    pilot.DrawStats(mStatsCanvas);
    mStatsCanvas.Draw(mSubCanvas, x, y);
}

CScreenPos CSplitScreen::GetGrabPos(const DisplayPilots &pilots) {
    CScreenPos pos = GetCentre(pilots);
    const float velFactor = 0.25; //screen modifier for speed

    if(pilots.size() == 1)
        pos += CScreenPos(pilots[0].GetVelocity() * velFactor);

    int x = GetRealGrabPos(pos.GetX(),
                           mSubCanvas.GetWidth(), mLevelCanvas->GetWidth());
    int y = GetRealGrabPos(pos.GetY(),
                           mSubCanvas.GetHeight(), mLevelCanvas->GetHeight());
    return CScreenPos(x, y);
}


int CSplitScreen::GetRealGrabPos(int pos, int subLength, int levelLength) {
    pos -= subLength / 2;
    if (pos > levelLength - subLength) pos = levelLength - subLength;
    if (pos < 0) pos = 0;
    return pos;
}


CScreenPos CSplitScreen::GetCentre(const DisplayPilots& pilots) {
    if(pilots.size() == 1)
        return { (int)pilots[0].GetPosition().GetX(),
                (int)pilots[0].GetPosition().GetY() };

    const auto humans = GetHumans(pilots);
    std::vector<int> sx, sy;
    for(const auto& p: humans) {
        sx.push_back(p.GetPosition().GetX());
        sy.push_back(p.GetPosition().GetY());
    }

    const int minX = *std::min_element(std::begin(sx), std::end(sx));
    const int maxX = *std::max_element(std::begin(sx), std::end(sx));
    const int minY = *std::min_element(std::begin(sy), std::end(sy));
    const int maxY = *std::max_element(std::begin(sy), std::end(sy));

    if(maxX - minX < mSubCanvas.GetWidth() - kSplitBorder &&
       maxY - minY < mSubCanvas.GetHeight() - kSplitBorder) //everyone together
        return { (maxX+minX)/2, (maxY+minY)/2 };
    else
        return { -1, -1 };
}


auto CSplitScreen::GetHumans(const DisplayPilots& pilots) -> DisplayPilots{
    DisplayPilots humans;
    for(unsigned int i = 0; i < pilots.size(); i++)
        if(pilots[i].HasSplitScreen()) humans.push_back(pilots[i]);
    return humans.empty() ? pilots : humans;
}
