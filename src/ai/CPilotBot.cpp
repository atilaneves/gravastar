#include "CPilotBot.hpp"
#include "CPilotFactory.hpp"
#include "CPilotInputBot.hpp"
#include "CShip.hpp"
#include "CBotAction.hpp"
#include "CActionPicker.hpp"
#include "CLevel.hpp"
#include "CPilots.hpp"
#include "CInvulnerable.hpp"
#include <math.h>


REG_PILOT("Bot", CPilotBot)


CPilotBot::CPilotBot(const CPilotOptions &options,
                     const CShipYard &shipYard,
                     CMeleeScore& meleeScore):
    CPilot(false/*split screen*/, options, shipYard, meleeScore),
    mMinAngle(0.1), mActionPicker(new CActionPicker(*this)) {

}


void CPilotBot::CheckControls(CClientSocket* clientSocket) {
    if(!IsAlive() || !GetShip().IsActive()) return;
    CBotAction &action = mActionPicker->GetAction();
    CPilotInputBot input;
    Turn(action, input);
    Thrust(action, input);
    Shoot(action, input);
    PreventStasis(input);
    GetShip().ApplyInput(input);
}


void CPilotBot::PreventStasis(CPilotInputBot& input) {
    //to avoid the pilot getting stuck and not thrusting
    if(input.Thrust()) mNoThrust.Reset(); //all gd, thrusting
    if(!input.Thrust() && !mNoThrust.IsActive()) mNoThrust.Start(10);
    if(!input.Thrust() && mNoThrust.JustFinished()) mThrust.Start(0.5);
    if(mThrust.IsActive()) {
        input.SetThrust();
        int r = rand() % 6;
        if(r == 0)      input.SetLeft();
        else if(r == 1) input.SetRight();
    }
}


void CPilotBot::Turn(const CBotAction& action, CPilotInputBot& input) {

    double noseAngle = action.GetNoseAngle(); //where we want to be
    double shipAngle = CNose::NoseIndex2Angle(GetShip().GetNose());

    //so it doesn't toggle bet. 2 frames, only change if big diff
    if(fabs(shipAngle - noseAngle) > mMinAngle) {
        if((shipAngle < noseAngle && fabs(shipAngle-noseAngle) < M_PI) ||
           (shipAngle > noseAngle && fabs(shipAngle-noseAngle) > M_PI))
            input.SetRight();
        else
            input.SetLeft();
    }
}


void CPilotBot::Thrust(const CBotAction& action, CPilotInputBot& input) {

    int targetIndex   = action.GetTargetIndex();
    float targetAngle = action.GetTargetAngle();
    float dist2 = 0;
    if(targetIndex != -1  && !CActionPicker::IsNearlyDead(GetShip())) {
        //don't thrust if nearly dead (dist is still 0)
        CVector2 dist = CPilots::GetPilot(targetIndex).GetShip().GetPos() -
            GetShip().GetPos();
        dist2 = dist.Radius2();
    }

    const int kMinDist2 = 75*75; //how close we want to get to them
    if(targetIndex == -1 || dist2 > kMinDist2) { //no need if we're close
        float shipAngle = CNose::NoseIndex2Angle(GetShip().GetNose());
        //thrust if we're not past it
        if(CVector2(shipAngle) * CVector2(targetAngle) > 0) input.SetThrust();
    }
}


void CPilotBot::Shoot(CBotAction& action, CPilotInputBot& input) {

    int targetIndex = action.GetTargetIndex();
    if(targetIndex == -1) return;
    if(CPilots::GetPilot(targetIndex).GetShip().
       IsEffectOn(CInvulnerable::GetID())) return; //don't shoot superman!

    CVector2 shipPos = CPilots::GetPilot(targetIndex).GetShip().GetPos();
    CVector2 dist    = shipPos - GetShip().GetPos();
    const float kCloseUp = 40; //more lenient close up
    const float radius = dist.Radius();
    float theta = dist.Theta(); //deviation from the target we accept
    if(theta < 0) theta += 2*M_PI;
    const float maxDeltaAngle = radius < kCloseUp ? mMinAngle*1.2 : mMinAngle*3;

    //shoot if facing right way
    float weaponAngle = CNose::NoseIndex2Angle(GetShip().GetNose()) +
                                         action.GetWeaponAngle();
    if(weaponAngle > 2*M_PI) weaponAngle -= 2*M_PI;
    if(action.WantsToShoot() ||
       (fabs(weaponAngle - theta) < maxDeltaAngle &&
        (IsClearLine(shipPos) || radius < kCloseUp))) //we can take a shot
        action.SetShootControl(input); //action picks right weapon
}


void CPilotBot::NextShip() {
    CPilot::NextShip();
    if(!GetNbShips()) return;
    mActionPicker.reset(new CActionPicker(*this)); //might be new ship...
}


bool CPilotBot::IsClearLine(const CVector2 &pos) {
    CShip& ship = GetShip();
    return ship.GetLevel().IsClearLine(ship.GetPos().GetX(),
                                       ship.GetPos().GetY(),
                                       pos.GetX(), pos.GetY());
}
