#include "CSuperExplosion.hpp"
#include "CShip.hpp"
#include "CShips.hpp"


CSuperExplosion::CSuperExplosion(CLevel &level, const CVector2& pos,
				 const CSpriteVector &sprites,
				 const CSound &sound, CShip& ship):
    CExplosion(level, pos, sprites, sound, kSpeed),
    mShip(ship) { 

}


void CSuperExplosion::Draw() {
  CExplosion::Draw(); 
  if(CShips::HasShip(&mShip) && mShip.IsAlive()) mShip.Draw();
}
