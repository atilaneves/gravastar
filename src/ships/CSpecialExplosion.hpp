#ifndef CSPECIALEXPLOSION_H
#define CSPECIALEXPLOSION_H


#include "CExplosion.hpp"
class CShip;


class CSpecialExplosion: public CExplosion {

public:

  enum { kNbFrames = 10, kSpeed = 475 }; //200 is 1 frame/s

  CSpecialExplosion(CLevel &level, const CVector2& pos,
		    const CSpriteVector &sprites,
		    const CSound &sound, CShip& ship);

private:

  CShip &mShip;


};

#endif
