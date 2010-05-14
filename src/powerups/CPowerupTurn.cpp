#include "CPowerupTurn.hpp"
#include "CPowerupFactory.hpp"
#include "CTurnUp.hpp"
#include "CShip.hpp"


REG_POWERUP("turn", CPowerupTurn) //register in the factory


CPowerupTurn::CPowerupTurn(CPowerups &powerups,
			   CLevel &level, const CVector2 &pos,
			   const CGravSprite& sprite):
  CPowerup(powerups, level, pos, sprite) {


}


void CPowerupTurn::AffectShip(CShip &ship) {
 ship.StartEffect(CTurnUp::GetID()); //start the effect
}
