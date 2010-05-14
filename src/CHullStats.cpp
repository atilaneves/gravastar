#include "CHullStats.hpp"
#include "CPilot.hpp"
#include "CCanvas.hpp"
#include "CShip.hpp"
#include "CTeam.hpp"
#include "CColour.hpp"
#include "CRect.hpp"
#include "CRectFill.hpp"



CHullStats::CHullStats(const CPilot& pilot, CCanvas& canvas):
   mPilot(pilot), mCanvas(canvas) {

}


void CHullStats::Draw() {

 CShip& ship = mPilot.GetShip();
 const int kMaxHull  = 50; //reference
 const int kMaxWidth = 80;
 const int kOuterRim = 2;

 const int x0 = 37, y0 = 1; //where hull bar starts
 const int w0 = int(kMaxWidth*(ship.GetMaxHull()/kMaxHull)) + kOuterRim;
 const int h0 = 6;

 CRect rect(mCanvas, x0 , y0, x0+w0-1, y0+h0-1, CColour::GetWhite());

 const int x1 = x0 + kOuterRim/2;
 const int y1 = y0 + kOuterRim/2;
 int w1 = int(kMaxWidth*ship.GetHull()/kMaxHull);
 if(w1<0) w1=0; //has to go forward...
 const int h1 = h0 - kOuterRim;

 if(w1) CRectFill rectFill(mCanvas, x1, y1, x1+w1-1, y1+h1-1,
			   mPilot.GetTeam().GetMainColour());

}
