#ifndef CACTIONPICKER_H
#define CACTIONPICKER_H


#include "CSeekAndDestroy.hpp"
#include "CFlee.hpp"
#include "CWait.hpp"
#include "CSeekPowerup.hpp"
#include <memory>
class CBotAction;
class CPilotBot;
class CShip;
class CPowerups;


class CActionPicker {

public:

  CActionPicker(CPilotBot& pilot);

  static void SetPowerups(CPowerups* p) { sPowerups = p; }

  CBotAction& GetAction();
  static bool IsGaugeBelow(CShip &ship, float amount);
  static bool IsNearlyDead(CShip &ship);


private:

  CPilotBot& mPilot;
  bool mWasRecharging;
  std::auto_ptr<CSeekAndDestroy> mSeekAndDestroy;
  CFlee mFlee;
  CWait mWait;
  CSeekPowerup mSeekPowerup;

  static CPowerups* sPowerups;

  CBotAction& PickAction();


};


#endif
