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

    float GetMinAngle()    const { return mMinAngle; }
    bool  IsClearLine(const CVector2 &pos);
    virtual void  NextShip() override;


private:

    CTimeCounter mThrust, mNoThrust;
    float mMinAngle;
    std::unique_ptr<CActionPicker> mActionPicker;

    virtual void CheckControls(CClientSocket* clientSocket) override;

    void PreventStasis(CPilotInputBot& input);
    void Turn(const CBotAction& action, CPilotInputBot& input);
    void Thrust(const CBotAction& action, CPilotInputBot& input);
    void Shoot(CBotAction& action, CPilotInputBot& input);


};


#endif
