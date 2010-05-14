#include "CPowerupSpecial.hpp"
#include "CPowerupFactory.hpp"
#include "CShip.hpp"


REG_POWERUP("special", CPowerupSpecial) //register in the factory


CPowerupSpecial::CPowerupSpecial(CPowerups &powerups,
				 CLevel &level, const CVector2 &pos,
				 const CGravSprite& sprite):
   CPowerup(powerups, level, pos, sprite) {


}


void CPowerupSpecial::AffectShip(CShip &ship) {
 double amount = 1000; //err on the plus side
 ship.GetWeapons().AddSpecialGauge(amount);
}
