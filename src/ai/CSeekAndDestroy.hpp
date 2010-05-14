#ifndef CSEEKANDDESTROY_H
#define CSEEKANDDESTROY_H


#include "CBotAction.hpp"
#include "CVector2.hpp"
class CPilot;


class CSeekAndDestroy:public CBotAction {

public:

 CSeekAndDestroy(CPilotBot &pilot);

  virtual void Think();


protected:

  virtual void SetShootControl(CPilotInputBot &input);
          bool IsTooHot();


private:

  bool mPointAtTarget;
  bool mWait;

  bool     IsValidTarget(const CPilot& pilot);
  int      FindTarget(CVector2& pos);
  float    FindTargetAngle(const CVector2& pos);
  CVector2 SetNearestPoint(const CVector2& pos, float pullAngle);

};


#endif
