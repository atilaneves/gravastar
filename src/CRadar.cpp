#include "CRadar.hpp"
#include "CPilot.hpp"
#include "CTeam.hpp"
#include "CRectFill.hpp"
#include "CCircle.hpp"
#include "CShip.hpp"
#include <math.h>


CRadar::CRadar():
  mCanvas(kRadius*2+1, kRadius*2+1) {

}


void CRadar::Draw(CBitmap &bmp, int x, int y, const pilots_t &pilots,
		  const pilots_t& humans, const CScreenPos &centrePos) {

  mCanvas.Clear(makecol(255, 0, 255));
  const CTeam &team = humans.size()== 1 ? humans[0]->GetTeam() : CTeam::sWhite;
  int col = team.GetMainColour();

  int width  = mCanvas.GetWidth();
  int height = mCanvas.GetHeight();
  int radius = width/2;

  CCircle c(mCanvas, width/2, height/2, radius, col);
  const int blipWidth = 3; //square blips
  int x0 = width/2  - blipWidth/2;
  int y0 = height/2 - blipWidth/2;

  CRectFill r(mCanvas, x0, y0, x0 + blipWidth - 1,y0 + blipWidth - 1,col); //us
  CVector2 centre(centrePos.GetX(), centrePos.GetY());

  for(unsigned int p = 0; p < pilots.size(); p++) {
    if(!pilots[p]->GetShip().IsAlive()) continue;
    col = pilots[p]->GetTeam().GetMainColour();
    CVector2 where = CalcRadiusAngle(*pilots[p], centre);
    where += CVector2(width/2 - blipWidth/2, height/2 - blipWidth/2);
    CScreenPos corner1(int(where.GetX()), int(where.GetY()));
    CScreenPos corner2 = corner1 + CScreenPos(blipWidth-1, blipWidth-1);
    CRectFill rr(mCanvas, corner1, corner2, col);
  }

  mCanvas.Draw(bmp, x - width + 1, y);
}


CVector2 CRadar::CalcRadiusAngle(const CPilot &pilot, const CVector2& centre) {

  CVector2 dPos = pilot.GetShip().GetPos() - centre;
  const float kMaxDistance = 600; //maximum scanner range
  if(dPos.Radius() > kMaxDistance) dPos *= kMaxDistance/dPos.Radius();
  const int kMaxRadius = mCanvas.GetWidth()/2 - 3;
  dPos *= kMaxRadius / kMaxDistance;

  return dPos;
}
