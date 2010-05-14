#include "CPowerup.hpp"
#include "CPowerups.hpp"
#include "CShip.hpp"


CPowerup::CPowerup(CPowerups& powerups, CLevel &level, const CVector2 &pos,
		   const CGravSprite& sprite):
  CSpriteObj(level, pos),
  mPowerups(powerups), mSprite(sprite), mActive(true) {

}


CPowerup::~CPowerup() {
  mPowerups.Remove(this);
}


void CPowerup::Update(float dt) {
  CheckCollision(dt);
}


void CPowerup::Hit(CSpriteObj& obj, CScreenPos pos, float dt) {
  CShip *ship = dynamic_cast<CShip*>(&obj);
  if(ship) Hit(*ship, pos, dt);
}


void CPowerup::Hit(CShip& ship, CScreenPos pos, float dt) {
  AffectShip(ship);
  mActive = false;
}

