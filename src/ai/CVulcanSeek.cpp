#include "CVulcanSeek.hpp"
#include "CSeekFactory.hpp"
#include "CPilotBot.hpp"
#include "CPilots.hpp"
#include "CScramble.hpp"
#include "CPilotInputBot.hpp"
#include "CVulcan.hpp"
#include "CShip.hpp"



REG_SEEK("Vulcan", CVulcanSeek)


CVulcanSeek::CVulcanSeek(CPilotBot &pilot):
   CSeekAndDestroy(pilot),
   mIsBombing(false), mIsClustering(false) {

}


void CVulcanSeek::Think() {
  CSeekAndDestroy::Think();
  mIsBombing = mIsClustering = false;
  if(mPilot.GetShip().GetWeapons().IsSuperActive()) return;
  
  if(mTargetIndex != -1) { //we have a target
    const CShip &ship = CPilots::GetPilot(mTargetIndex).GetShip();
    CVulcan *vulcan = (CVulcan*)&mPilot.GetShip();
    
    if(!vulcan->IsSpecialActive() && //no cluster active
       //no super, above its target, has clear line, and has mines
       vulcan->GetPos().GetY() < ship.GetPos().GetY() && 
       vulcan->GetWeapons().CanSpecial() &&
       mPilot.IsClearLine(ship.GetPos())) {
      mNoseAngle += M_PI;
      if(mNoseAngle > 2*M_PI) mNoseAngle -= 2*M_PI; //keep it in range
      mIsBombing = true;
    }
    else {
      CVector2 pos = vulcan->GetSpecialPos();
      if(vulcan->IsSpecialActive() && pos.GetY() < ship.GetPos().GetY() &&
	 (ship.GetPos() - pos).Radius() < 200)
	mIsClustering = true; //cluster!
    }
  }
}


void CVulcanSeek::SetShootControl(CPilotInputBot &input) {
  if(mPilot.GetShip().GetWeapons().CanSuper())
    input.SetSuper();
  else if(mIsBombing || mIsClustering)
    input.SetSpecial();
  else if(!IsTooHot()) //not waiting to cool down, fire away!
    input.SetWeapon();
}


float CVulcanSeek::GetWeaponAngle() const {
 if(mIsBombing) //bombs come out of the back, but gravity plays a part
    return M_PI - (M_PI_2 - mTargetAngle) / 10;
 else
    return 0; //lava cannon mounted on the front
}
