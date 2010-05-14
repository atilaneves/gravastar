#include "CPowerupInvulnerable.hpp"
#include "CPowerupFactory.hpp"
#include "CPilot.hpp"
#include "CShip.hpp"
#include "CInvulnerable.hpp"


REG_POWERUP("invulnerable", CPowerupInvulnerable) //register in the factory


CPowerupInvulnerable::CPowerupInvulnerable(CPowerups &powerups,
					   CLevel &level, const CVector2 &pos,
					   const CGravSprite& sprite):
    CPowerup(powerups, level, pos, sprite) {

}


void CPowerupInvulnerable::AffectShip(CShip& ship) {
  float duration = 7.5; //lasts longer than usual
  ship.StartEffect(CInvulnerable::GetID(), duration); //start off invulnerable
}
