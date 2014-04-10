#include "CPowerupWeapon.hpp"
#include "CPowerupFactory.hpp"
#include "CCoolant.hpp"
#include "CShip.hpp"


REG_POWERUP("weapon", CPowerupWeapon) //register in the factory


CPowerupWeapon::CPowerupWeapon(CPowerups &powerups,
			       CLevel &level, const CVector2 &pos,
			       const CGravSprite& sprite):
   CPowerup(powerups, level, pos, sprite) {


}


void CPowerupWeapon::AffectShip(CShip &ship) {
  ship.StartEffect(CCoolant::GetID());
}
