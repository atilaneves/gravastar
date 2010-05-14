#include "CEngine.hpp"
#include "CPilotInput.hpp"
#include "CShipBluePrint.hpp"
#include "CShip.hpp"
#include "CFollower.hpp"
#include "CFlicker.hpp"
#include "CSound.hpp"
#include "CThrustUp.hpp"
#include "CEMP.hpp"
#include "CEMB.hpp"
#include "CSpriteObjs.hpp"
#include <math.h>


CEngine::CEngine(const CShipBluePrint &bluePrint, CLevel &level, CShip &ship):
  mOn(false),
  mThrust(bluePrint.mThrust), mMaxVel(bluePrint.mMaxVel), mExaust(0),
  mLevel(level), mShip(ship),
  mExaustSprites(bluePrint.GetExaustSprites()),
  mSound(bluePrint.mSounds.mExaustSound) {

}


void CEngine::ApplyInput(const CPilotInput &controls) {
  mOn = controls.Thrust();
  if(mShip.IsEffectOn(CEMP::GetID()) && !mShip.IsEffectOn(CEMB::GetID()))
    mOn = false;
  mOn ? ExaustOn() : ExaustOff();
}


void CEngine::Reset() {
  mOn = false;
  ExaustOff();
}


void CEngine::ExaustOn() {
  if(CSpriteObjs::HasFlicker(mExaust)) return; //already on, no need
  float volume = 1;
  bool loop = true;
  mSound.Play(mShip.GetPos(), volume, loop);
  const float kExaustHz = 70;
  mExaust = new CFlicker(kExaustHz, mLevel,
			 new CFollower(mExaustSprites, mLevel, mShip));
}



void CEngine::ExaustOff() {
  if(CSpriteObjs::HasFlicker(mExaust)) mExaust->Die();
  mExaust = 0;
  mSound.Stop();
}


CVector2 CEngine::CalcAcc(float angle) const {

  CVector2 acc(0, 0); //default is not thrusting

  if(mOn) {
    acc += GetThrust() * CVector2(angle);
    acc *= SpeedFactor(acc, mShip.GetVel()); //decrease acc if going fast
  }

  return acc;
}


float CEngine::SpeedFactor(const CVector2 &acc, const CVector2 &vel) const {
//decrease acc as we speed up if thrusting forwards

  float invGamma = 1; //no change by default

  if(acc * vel > 0) { //forwards it is
    float velocity = vel.Radius();
    float maxVel   = GetMaxVel();
    invGamma = 1 - (velocity/maxVel)*(velocity/maxVel);
  }
  
  return invGamma;
}


float CEngine::GetMaxVel() const {
  return mShip.IsEffectOn(CThrustUp::GetID()) ? mMaxVel * 1.5 : mMaxVel;
}


float CEngine::GetThrust() const {
  return mShip.IsEffectOn(CThrustUp::GetID()) ? mThrust * 3 : mThrust;
}
