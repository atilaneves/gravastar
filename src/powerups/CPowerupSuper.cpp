#include "CPowerupSuper.hpp"
#include "CPowerupFactory.hpp"
#include "CPilot.hpp"
#include "CShip.hpp"


REG_POWERUP("super", CPowerupSuper) //register in the factory


CPowerupSuper::CPowerupSuper(CPowerups &powerups,
			     CLevel &level, const CVector2 &pos,
			     const CGravSprite& sprite):
  CPowerup(powerups, level, pos, sprite) {

}


void CPowerupSuper::AffectShip(CShip& ship) {
  float amount = -1;
  ship.GetPilot().AddDamage(amount, ship.GetPilot()); //instant super!
}
