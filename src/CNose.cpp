#include "CNose.hpp"
#include "CPilotInput.hpp"
#include "CShipBluePrint.hpp"
#include "CShip.hpp"
#include "CTurnUp.hpp"
#include <math.h>


CNose::CNose(const CShipBluePrint &bluePrint, CShip& ship):
  mTurnPower(bluePrint.mTurnPower),
  mNose(kNbNoses/4), mOmega(0), mLastUpdate(0), mShip(ship) {

}


void CNose::ApplyInput(const CPilotInput &controls) {
  if(mSpinCounter.IsActive()) return; //don't bother if spinning
  mOmega = 0; 
  if(controls.Left())  mOmega += mTurnPower; //could add up to 0 if
  if(controls.Right()) mOmega -= mTurnPower; //both of them are pressed
}


void CNose::Update(float dt) { 
  float amount = mOmega * dt;
  if(mShip.IsEffectOn(CTurnUp::GetID())) amount*=1.5; //powerup!
  mNose += amount;
  mLastUpdate = amount;
}


void CNose::BackTrack() { 
  mNose -= mLastUpdate; 
}


float CNose::GetAngle() const {
  return NoseIndex2Angle(GetNose());
}


float CNose::NoseIndex2Angle(int nose) {
  return 2*M_PI*((kNbNoses - nose) / float(kNbNoses));
}


int CNose::GetNose() const {
 int nose = int(mNose) % kNbNoses;
 if(nose < 0) nose += kNbNoses; //makes sure it's in the interval
 return nose;
}


void CNose::Set(float orientation, float omega) { 
 mNose  = orientation;
 mOmega = omega; 
}


int CNose::Angle2NoseIndex(float angle) {
  if(angle < M_PI/16) angle += 2*M_PI;
  return int(kNbNoses - angle/(2*M_PI) * kNbNoses + 0.001);
}


void CNose::Spin(const CVector2& force) {
 mOmega = force.Radius() / 7.5;
 float angle = force.Theta();
 if(angle < 0) angle += 2*M_PI; //make it go from 0 to 2pi
 if(GetAngle() > angle) mOmega *= -1; //turn in the right direction
 mSpinCounter.Start(force.Radius() / 800); //tick away
}
