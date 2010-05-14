#ifndef CSUPEREXPLOSION_H
#define CSUPEREXPLOSION_H


#include "CExplosion.hpp"
#include "CShip.hpp"


class CSuperExplosion: public CExplosion {

public:

  enum { kNbFrames = 8, kSpeed = 125 }; //200 is 1 frame/s

  
  CSuperExplosion(CLevel &level, const CVector2& pos,
		  const CSpriteVector &sprites,
		  const CSound &sound, CShip& ship):
    CExplosion(level, pos, sprites, sound, kNbFrames, kSpeed),
    mShip(ship) { }


private:

  CShip &mShip;

 virtual void Draw() { CExplosion::Draw(); 
                       if(mShip.IsActive()) 
			  mShip.Draw(); }


};

#endif
