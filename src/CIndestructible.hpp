#ifndef CINDESTRUCTIBLE_H
#define CINDESTRUCTIBLE_H


#include "COneSpriteObj.hpp"
#include "CSound.hpp"


class CIndestructible: public COneSpriteObj {

public:

  CIndestructible(CLevel &level, const CVector2 &pos, CGravSprite *sprite,
		  const CSound& klang);

  virtual void Erase()          { Draw(); } //always there to be hit
  virtual void Hit(CSpriteObj& obj, CScreenPos pos, float dt);
  virtual void Hit(CShip&     ship, CScreenPos pos, float dt);
  virtual void Hit(CProjectile& proj, CScreenPos pos, float dt);
  virtual void Update(float dt) { }


private:

  CSound mKlang;

  virtual void ShipLanded(CShip& ship, float dt) { } //if it lands...


};


#endif
