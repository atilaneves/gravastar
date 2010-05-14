#include "CDeflector.hpp"
#include "CProjectile.hpp"
#include "CShip.hpp"



CDeflector::CDeflector(const CSpriteVector &sprites, CLevel &level,
		       CMoverObj &obj, CSound *sound , const CVector2& offset):
  CFollower(sprites, level, obj, sound, offset) {


}


void CDeflector::Hit(CSpriteObj& obj, CScreenPos pos, float dt) {
  CProjectile *proj = dynamic_cast<CProjectile*>(&obj);
  if(proj) Hit(*proj, pos, dt);
}


void CDeflector::Hit(CProjectile& proj, CScreenPos pos, float dt) {
  proj.Move(-dt);
  bool grav        = fabs(proj.CalcAcc().Radius()) > 1e-3;
  float thetaPrime = GetThetaPrime(proj, pos, grav);
  if(thetaPrime < 0) return; //don't reflect from the inside
  float velNorm    = GetVelNorm(proj, grav);
  CVector2 newVel  = CVector2(thetaPrime) * velNorm;
  if(grav) newVel += mFollowed.GetVel();
  proj.SetVel(newVel);
  if(proj.IsUpdated()) proj.Erase();
  proj.Move(dt);
  if(proj.IsUpdated()) proj.Draw();
}


float CDeflector::GetThetaPrime(const CProjectile& proj, const CScreenPos& pos,
				bool grav) const {
  CVector2 vel = grav ? proj.GetVel() - mFollowed.GetVel() : proj.GetVel();
  CVector2 dPos = mFollowed.GetPos() - CVector2(pos.GetX(),pos.GetY());
  float alpha     = dPos.Angle(vel);
  float theta     = M_PI_2 - alpha;
  if(theta < 0) return theta; //don't reflect from the inside
  float projTheta = vel.Theta();
  return projTheta > dPos.Theta() ? projTheta + 2*theta : projTheta - 2*theta;
}


float CDeflector::GetVelNorm(const CProjectile& proj, bool grav) const {
  const float kMassFactor = 50;
  const float elasticity  = 1.5;
  return !grav ? proj.GetVel().Radius() :
    elasticity * ((2 * kMassFactor * mFollowed.GetVel().Radius() -
     kMassFactor * proj.GetVel().Radius())  / kMassFactor);
}


void CDeflector::Move(float dt) {
  CFollower::Move(dt);
  CheckCollision(dt);
}
