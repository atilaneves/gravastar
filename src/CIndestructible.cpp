#include "CIndestructible.hpp"
#include "CShip.hpp"
#include "CProjectile.hpp"
#include "CLevel.hpp"
#include "CColour.hpp"
#include <math.h>

CIndestructible::CIndestructible(CLevel &level, const CVector2 &pos,
				 CGravSprite *sprite, const CSound& klang):
  COneSpriteObj(level, pos, sprite),
  mKlang(klang) {


}


void CIndestructible::Hit(CSpriteObj& obj, CScreenPos pos, float dt) {
  CShip*       ship = dynamic_cast<CShip*>(&obj);
  CProjectile* proj = dynamic_cast<CProjectile*>(&obj);

 if(ship)      Hit(*ship, pos, dt);
 else if(proj) Hit(*proj, pos, dt);
}


void CIndestructible::Hit(CShip& ship, CScreenPos pos, float dt) {

  float edgeAngle; //gets set below
  bool landed = ship.BouncedOff(pos, edgeAngle);

  if(landed) ShipLanded(ship, dt);
  else ship.LandDamage(10*dt);

  //only if ship is moving towards us
  if(CVector2(edgeAngle) * ship.GetVel() < 0) ship.BounceOff(edgeAngle, dt);
  ship.PullBack(*this, edgeAngle);
  Draw(); //plug the hole
  if(ship.GetVel().Radius2() > 5) mKlang.Play(ship.GetPos());
  ship.CheckCollision(dt);
}


void CIndestructible::Hit(CProjectile& proj, CScreenPos pos, float dt) {
 proj.Die();
 Draw(); //plug the hole
}
