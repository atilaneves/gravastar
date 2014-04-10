#include "CProjectiles.hpp"
#include "CProjectile.hpp"
#include "CLevel.hpp"
#include "CShips.hpp"
#include "CShip.hpp"
#include <algorithm>
#include <math.h>


projs_t CProjectiles::sProjectiles;



projPlace_t CProjectiles::AddProjectile(CProjectile *projectile) {
  return sProjectiles.insert(sProjectiles.end(), projectile);
}


void CProjectiles::RemoveProjectile(CProjectile *projectile) {
  auto where = find(sProjectiles.begin(), sProjectiles.end(), projectile);
  if(where != sProjectiles.end()) sProjectiles.erase(where);
}


void CProjectiles::RemoveAll() {
  sProjectiles.erase(sProjectiles.begin(), sProjectiles.end());
}


void CProjectiles::DamageAll(const CVector2& collision,
                             float damage) {
  for (auto &sProjectile : sProjectiles) {
    CVector2 direction = (sProjectile)->GetPos() - collision;
    (sProjectile)->LoseHull(damage * CShips::GetDistanceScaling(direction));
  }
}


static const float kMaxDist = 150;
bool CProjectiles::HasTowards(const CShip& ship) {
  //anybody heading towards this position?
  for (auto &sProjectile : sProjectiles) {
    const CVector2 posDiff = ship.GetPos() - (sProjectile)->GetPos();
    const CVector2 &projVel = (sProjectile)->GetVel();
    const float maxAngle    = GetMaxAngle(ship.GetWidth(), posDiff.Radius());
    if(posDiff.Radius() < kMaxDist && posDiff.Angle(projVel) < maxAngle)
      return true; //close enough and pointing towards us
  }

  return false;
}


float CProjectiles::GetMaxAngle(int width, float radius) {
    const float kCloseDist = 20 + width / 2;
    return radius < kCloseDist ? 0.25 * M_PI * exp(-radius/kMaxDist) :M_PI_2;
}
