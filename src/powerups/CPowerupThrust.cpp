#include "CPowerupThrust.hpp"
#include "CPowerupFactory.hpp"
#include "CThrustUp.hpp"
#include "CShip.hpp"


REG_POWERUP("thrust", CPowerupThrust) //register in the factory


CPowerupThrust::CPowerupThrust(CPowerups &powerups, 
			       CLevel &level, const CVector2 &pos,
			       const CGravSprite& sprite):
  CPowerup(powerups, level, pos, sprite) {


}


void CPowerupThrust::AffectShip(CShip& ship) {
 ship.StartEffect(CThrustUp::GetID()); //start the effect
}
