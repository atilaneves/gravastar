#include "CHullStats.hpp"
#include "CPilot.hpp"
#include "CCanvas.hpp"
#include "CShip.hpp"
#include "CTeam.hpp"
#include "CColour.hpp"
#include "CRect.hpp"
#include "CRectFill.hpp"
#include "Cereal.hpp"



CHullStats::CHullStats(uint8_t teamHash, int8_t hull, int8_t maxHull):
    mTeamHash(teamHash), mHull(hull), mMaxHull(maxHull) {

}


void CHullStats::Draw(CCanvas& canvas) const {
    const int kMaxHull  = 50; //reference
    const int kMaxWidth = 80;
    const int kOuterRim = 2;

    const int x0 = 37, y0 = 1; //where hull bar starts
    const int maxHullWidth = (kMaxWidth * mMaxHull) / kMaxHull;
    const int w0 = maxHullWidth + kOuterRim;
    const int h0 = 6;

    CRect rect(canvas, x0 , y0, x0 + w0 - 1, y0 + h0 - 1, CColour::GetWhite());

    const int x1 = x0 + kOuterRim/2;
    const int y1 = y0 + kOuterRim/2;
    int w1 = (kMaxWidth * mHull) / kMaxHull;
    if(w1 < 0) w1 = 0; //has to go forward
    const int h1 = h0 - kOuterRim;

    const CTeam& team = CTeam::FromHash(mTeamHash);
    if(w1) CRectFill rectFill(canvas, x1, y1, x1 + w1 - 1, y1 + h1 - 1,
                              team.GetMainColour());
}

void CHullStats::cerealise(Cereal& cereal) {
    cereal.grain(mTeamHash);
    cereal.grain(mHull);
    cereal.grain(mMaxHull);
}
