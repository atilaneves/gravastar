#include "CFlicker.hpp"
#include "CSpriteObjs.hpp"
#include <math.h>


CFlicker::CFlicker(float frequency, CLevel &level, CSpriteObj *spriteObj):
  CSpriteObj(level, spriteObj->GetPos()),
  mDecorated(spriteObj), mFrequency(frequency), mFlicker(0), mDraw(false),
  mActive(true) {
  
  CSpriteObjs::RemoveObj(mDecorated.get()); //we update it

}


void CFlicker::Update(float dt) {
  if(mDecorated->IsStopped()) return;
  mDecorated->Update(dt);
  mFlicker += dt*mFrequency;
  mDraw = false;
  const float amount = 100*dt;

  if(mFlicker > amount) {
    mDraw = true;
    mFlicker -= amount;
  }
}
