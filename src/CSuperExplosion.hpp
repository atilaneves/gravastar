#ifndef CSUPEREXPLOSION_H
#define CSUPEREXPLOSION_H


#include "CExplosion.hpp"
class CShip;


class CSuperExplosion: public CExplosion {

public:

  enum { kNbFrames = 8, kSpeed = 125 };
  
  CSuperExplosion(CLevel &level, const CVector2& pos,
		  const CSpriteVector &sprites,
		  const CSound &sound, CShip& ship);

private:

  CShip &mShip;

  virtual void Draw();

};

#endif
