#include "CProjLauncher.hpp"
#include "CNose.hpp"
#include "CGravSprite.hpp"
#include "CShip.hpp"
#include <math.h>


CVector2 CProjLauncher::GetLaunchPos(const CGravSprite& sprite, float dt,
				     const CShip& ship,
				     float radius, float dAngle) {

  double posAngle   = CNose::NoseIndex2Angle(ship.GetNose());
  int    heights    = ship.GetSprite().GetHeight()/2 + sprite.GetHeight()/2;
  float  radiusSign = radius / fabs(radius);
  float velSign     = ship.GetVel().Radius() / fabs(ship.GetVel().Radius());
  return ship.GetPos() +
         CVector2(posAngle + dAngle) * radius * heights * 1.1 +
         radiusSign * velSign * ship.GetVel() * dt * 2; //get it out of the way
}



CVector2 CProjLauncher::GetLaunchVel(const CShip& ship,
				     float velNorm, float dVelAngle) {
  const float velAngle = CNose::NoseIndex2Angle(ship.GetNose()) + dVelAngle;
  return CVector2(velAngle) * velNorm;
}
