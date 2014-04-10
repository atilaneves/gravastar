#include "CPoint2D.hpp"
#include "CLevel.hpp"
#include "CShip.hpp"
#include <math.h>
#include <stdio.h>
#include <algorithm>


int CPoint2D::sMinStepSize = 20;
int CPoint2D::sMaxStepSize = 100;
int CPoint2D::sMaxNbStates = 0;
int CPoint2D::sNbPoints = 0;
int CPoint2D::sHalfWidth = 10;
const CLevel *CPoint2D::sLevel = nullptr;
static const float kSqrt2 = sqrt(2);
static const float kGreed = 0.65; //0 to 1, > means +accurate && +slower


CPoint2D::CPoint2D(int x,int y,int stepSize):
   mStepSize(stepSize), mOldStepSize(stepSize), mX(x), mY(y) {
  Constructor();
}


CPoint2D::CPoint2D(const CVector2& pos, int stepSize):
   mStepSize(stepSize), mOldStepSize(stepSize),
   mX(int(pos.GetX())), mY(int(pos.GetY())) {
  Constructor();
}


void CPoint2D::Constructor() {
 if(sNbPoints > 20)           mStepSize += sMinStepSize;
 if(mStepSize > sMaxStepSize) mStepSize  = sMaxStepSize;
 if(mStepSize < sMinStepSize) mStepSize  = sMinStepSize;
 mOldGreedSize = mOldStepSize * kGreed;
 sNbPoints++;
}


bool CPoint2D::IsAtGoal(CPoint2D *point) {
 return sNbPoints>200 || Distance(point) < 1.75*mStepSize;
}


float CPoint2D::Distance(CPoint2D *point) const {
  //diagonal distance works best here
  int dx = abs(point->GetX() - mX);
  int dy = abs(point->GetY() - mY);
  int minDir = std::min(dx, dy);
  int maxDir = std::max(dx, dy);
  //diagonal distance to close min dir, plus leftover in
  //direction of max dir
  return minDir * kSqrt2 + maxDir - minDir;
}


float CPoint2D::Estimate(CPoint2D *point) const {
  return Distance(point);
}


float CPoint2D::Cost(int op) {
  //even op is up, down, left, right, odd is diagonal
  float cost = op % 2 ? kSqrt2 * mOldGreedSize : mOldGreedSize;
  if(!IsFreeSquare(op)) cost *= kLandPenalty;
  return cost;
}


bool CPoint2D::IsFreeSquare(int op) {

  int dx,dy;
  SetDxDy(op, dx, dy);

  if(sNbPoints > 17) //less precision away from the start
    return sLevel->BlackPixel(mX - dx*(mOldStepSize/2),
                              mY + dy*(mOldStepSize/2));

  const int step = 1; //chk every pixel!
  int x = mX - dx * mOldStepSize; //all the way back to our mother node
  int y = mY + dy * mOldStepSize; //y is inverted
  //1st step, chk ship wings
  bool clearLine = sLevel->IsClearLine(x, y, mX, mY, step);
  if(sNbPoints <= 9 && clearLine) {
    int hx = dx * sHalfWidth;
    int hy = dy * sHalfWidth;
    clearLine = sLevel->IsClearLine(x+hy, y+hx, mX+hy, mY+hx, step) &&
                sLevel->IsClearLine(x-hy, y-hx, mX-hy, mY-hx, step);
  }

  return clearLine;
}


CPoint2D * CPoint2D::CreateState(int op) {

 int dx,dy;
 SetDxDy(op, dx, dy);
 int x = mX + dx*mStepSize; //move it in this dir.
 int y = mY - dy*mStepSize; //y is inverted
 const int side = 25;

 if(x >= 0 && x <= sLevel->GetWidth()  - 1 &&
    y >= 0 && y <= sLevel->GetHeight() - 1 &&
     sLevel->IsFreeSquare(int(x), int(y), side))
    return new CPoint2D(x, y, mStepSize);
 else
   return nullptr;
}


void CPoint2D::SetDxDy(int op,int &dx,int &dy) {
 //8 operators -> 0 is right, rotates anti-clockwise
 if(op == 2 || op == 6)      dx =  0;
 else if(op >= 3 && op <= 5) dx = -1;
 else                        dx =  1;

 if(op == 0 || op == 4)      dy =  0;
 else if(op >= 5 && op <= 7) dy = -1;
 else                        dy =  1;
}


float CPoint2D::OpToAngle(int op) { //operator to angle
  return 2*M_PI*(kNbAngles - op / float(kNbAngles));
}


int CPoint2D::GetIndex() const {
 return (mY/sMinStepSize)*(sLevel->GetWidth()/sMinStepSize) +
    mX/sMinStepSize;
}


void CPoint2D::SetMinStepSize(int s) {
 sMinStepSize = s;
 //0 to n = n+1 nodes, hence the +1 at the end
 int widthInSteps  = sLevel->GetWidth() /  sMinStepSize + 1;
 int heightInSteps = sLevel->GetHeight() / sMinStepSize + 1;
 sMaxNbStates = widthInSteps * heightInSteps;
}


void CPoint2D::SetStepSizes(CShip& ship, int min, int max) {
  SetMinStepSize(std::max(min, ship.GetHeight() / 2));
  SetMaxStepSize(max);
  SetHalfWidth(ship.GetWidth() / 2);
}
