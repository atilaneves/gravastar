#ifndef CPILOTBOT_H
#define CPILOTBOT_H


#include "CPilot.hpp"
#include "CActionPicker.hpp"
#include "CTimeCounter.hpp"
#include <memory>
class CBotAction;
class CPilotInputBot;


class CPilotBot: public CPilot {

public:

  CPilotBot(const CPilotOptions &options, const CShipYard &shipYard,
	    CMeleeScore& meleeScore);
  virtual ~CPilotBot() { }

          float GetMinAngle()    const { return mMinAngle; }
  virtual bool  HasSplitScreen() const { return false; }
          bool  IsClearLine(const CVector2 &pos);
  virtual void  NextShip();


private:

  CTimeCounter mThrust, mNoThrust;
  float mMinAngle;
  std::auto_ptr<CActionPicker> mActionPicker;

  virtual void CheckControls();

  void PreventStasis(CPilotInputBot& input);
  void Turn(const CBotAction& action, CPilotInputBot& input);
  void Thrust(const CBotAction& action, CPilotInputBot& input);
  void Shoot(CBotAction& action, CPilotInputBot& input);


};


#endif
