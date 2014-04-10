#ifndef CPROJLAUNCHER_H
#define CPROJLAUNCHER_H


#include "CScreenPos.hpp"
#include "CVector2.hpp"
class CGravSprite;
class CShip;


class CProjLauncher {

public:


  static CVector2 GetLaunchPos(const CGravSprite& sprite, float dt,
			       const CShip& ship,
			       float radius, float dAngle = 0);
  static CVector2 GetLaunchVel(const CShip& ship,
			       float velNorm, float dVelAngle = 0);

private:


};


#endif
