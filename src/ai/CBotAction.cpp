#include "CBotAction.hpp"
#include "CVector2.hpp"
#include "CPilotBot.hpp"
#include <math.h>


void CBotAction::SetNoseAngle(float cruiseSpeed) {

 CVector2 noseVel = cruiseSpeed * CVector2(mTargetAngle) -
                    mPilot.GetShip().GetVel();

 mNoseAngle = noseVel.Theta();
 if(mNoseAngle < 0) mNoseAngle += 2*M_PI;
 if(fabs(mNoseAngle - mTargetAngle) < mPilot.GetMinAngle())
    mNoseAngle = mTargetAngle; //to stop toggling between 2 frames

}
