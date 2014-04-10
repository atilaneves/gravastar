#include "CPowerupHull.hpp"
#include "CPowerupFactory.hpp"
#include "CShip.hpp"
#include "CSound.hpp"


REG_POWERUP("hull", CPowerupHull) //register in the factory


CPowerupHull::CPowerupHull(CPowerups &powerups, CLevel &level,
                           const CVector2 &pos,
                           const CGravSprite& sprite):
   CPowerup(powerups, level, pos, sprite) {

  //mSound=new CSound("repair"); //when ship gets hit w this powerup

}


void CPowerupHull::AffectShip(CShip& ship) {
 double amount = 1000; //err on the plus side
 ship.LoseHull(-amount, ship.GetPilot());
 //mSound->Play(ship->GetPosX(),ship->GetPosY());
}
