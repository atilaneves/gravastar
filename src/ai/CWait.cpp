#include "CWait.hpp"
#include "CPilotBot.hpp"
#include <math.h>



CWait::CWait(CPilotBot &pilot):
   CBotAction(pilot) {

}


void CWait::Think() {
 //don't do much...
 mTargetIndex = -1;
 mNoseAngle   = M_PI_2 + mPilot.GetShip().GetVel().GetX() * 0.01;
 mTargetAngle = 1.5 * M_PI;
}
