#include "CExplosion.hpp"
#include "CProjectile.hpp"


CExplosion::CExplosion(CLevel& level, const CVector2& pos, 
		       const CSpriteVector& sprites,
		       const CSound& sound, float speed):
  CSpriteObj(level, pos),
  mSprites(sprites), mSound(sound),
  mSpeed(speed), mFrame(0), mDead(false) {
  
  mSound.Play(GetPos());
}


void CExplosion::Update(float dt) {
  
  //update frame in FPS invariant way - 200 is 1 exp frame/s
  mFrame += (mSpeed * dt)/mSprites.GetNbSprites();
  
  if(mFrame >= mSprites.GetNbSprites()) { //explosion is over
    mFrame = mSprites.GetNbSprites() - 1; //to get last one
    mDead = true;
  }      
}


void CExplosion::Hit(CSpriteObj& obj, CScreenPos pos, float dt) {
  CProjectile *proj = dynamic_cast<CProjectile*>(&obj);
  if(proj) Hit(*proj, pos, dt); //hit projectile
}


void CExplosion::Hit(CProjectile& proj, CScreenPos pos, float dt) {
 proj.LoseHull(0.05);
}
