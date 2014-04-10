#ifndef CPOINT2D_H
#define CPOINT2D_H


#include "CVector2.hpp"
#include <math.h>
class CLevel;
class CShip;


class CPoint2D {

public:

  enum { kNbAngles = 8, kLandPenalty = 2000 };

  CPoint2D(int x, int y, int stepSize = 0);
  CPoint2D(const CVector2& pos, int stepSize = 0);
  ~CPoint2D() { sNbPoints--; }

  //search state interface
  bool      Equals(const CPoint2D &point) const { //needs to be FAST!!
    return mX == point.mX && mY == point.mY; }
  float     Estimate(CPoint2D *point) const;
  float     Cost(int op);
  CPoint2D  *CreateState(int op); //new state using operator op
  int        GetIndex() const;
  static int GetMaxNbStates() { return sMaxNbStates; }
  int        GetNbOperators() const { return kNbAngles; }
  bool       IsAtGoal(CPoint2D *point);

  //CPoint2D specific stuff
  int       GetStepSize() const    { return mStepSize; }
  int       GetX() const           { return mX;        }
  int       GetY() const           { return mY;        }
  static float OpToAngle(int op); //operator to angle
  static void SetHalfWidth(int hw)  { sHalfWidth=hw; }
  static void SetMinStepSize(int s);
  static void SetMaxStepSize(int s) { sMaxStepSize=s; }
  static void SetLevel(const CLevel &level) { sLevel = &level; }
  static void SetStepSizes(CShip& ship, int min, int max);


private:

  static int sMinStepSize;
  static int sMaxStepSize;
  static int sMaxNbStates;
  static int sNbPoints;
  static int sHalfWidth;
  static const CLevel* sLevel;
  int mStepSize;
  int mOldStepSize;
  int mX,mY;
  float mOldGreedSize;

  void  Constructor();
  float Distance(CPoint2D *point) const;
  void  GetCosSinOp(int op,float &cosAngle,float &sinAngle);
  bool  IsFreeSquare(int op);
  void  SetDxDy(int op,int &dx,int &dy);

};


#endif
