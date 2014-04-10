#include "CShips.hpp"
#include "CShip.hpp"
#include "CLevel.hpp"
#include "CInvulnerable.hpp"
#include "CEMP.hpp"
#include <algorithm>
#include <math.h>


ships_t CShips::sShips;



shipPlace_t CShips::AddShip(CShip *ship) {
  return sShips.insert(sShips.end(), ship);
}


void CShips::RemoveShip(CShip *ship) {
  auto where = find(sShips.begin(), sShips.end(), ship);
  if(where != sShips.end()) sShips.erase(where);
}


void CShips::RemoveAll() {
  sShips.erase(sShips.begin(), sShips.end());
}


bool CShips::HasShip(CShip *ship) {
  auto where = find(sShips.begin(), sShips.end(), ship);
  return where != sShips.end();
}


void CShips::StartEffect(const CShip* ship, int effect, float duration) {
  for (auto &sShip : sShips) {
    //process everyone except us
    if ((sShip)->IsAlive() && sShip != ship && !(sShip)->IsEffectOn(effect)) {
      CVector2 direction = (sShip)->GetPos() - ship->GetPos();
      float scale = GetDistanceScaling(direction);
      float realDuration = duration * scale;
      if(realDuration > 0.5) //only if big enough to be worth the bother
        (sShip)->StartEffect(effect, realDuration);
    }
  }
}


void CShips::PushAll(const CVector2& collision,
		     float force, CSpriteObj* hitShip, CPilot& pilot,
		     float damage) {

  for (auto &sShip : sShips) {
    //process everyone except the ship we hit
    if ((sShip)->IsAlive() && sShip != hitShip) {
      CVector2 direction = (sShip)->GetPos() - collision;
      float scale = GetDistanceScaling(direction);
      float speed = force * scale * 0.675;
      (sShip)->Push(CVector2(direction.Theta()) * speed, pilot);
      if(damage > 0)
        (sShip)->LoseHull(damage * scale, pilot);
    }
  }
}


float CShips::GetDistanceScaling(const CVector2& direction) {
  const float kPower = 2; //as in to the power of
  const float kAlpha = pow(1e-2, kPower); //distance scaling
  const float kMinRadius = 50;
  float radius = std::max(direction.Radius(), kMinRadius); //>=0
  return exp(-kAlpha * pow(radius - kMinRadius, kPower));
}


CShip* CShips::Find(const CScreenPos &pos, bool updated) {

  for (auto &sShip : sShips)
    if (((sShip)->IsUpdated() || !updated) && (sShip)->IsAlive() &&
        (sShip)->InSprite(pos))
      return sShip;

  return nullptr; // didn't find any ships
}


bool CShips::IsClearLine(const CShip &ship, int x, int y) {

  for (auto &sShip : sShips) {
    if ((sShip)->IsAlive() && sShip != &ship &&
        ship.GetLevel().IsClearLine((sShip)->GetPos(), CVector2(x, y)))
      return true;
  }

 return false; //nobody else has a clear line of sight to x,y
}


bool CShips::IsAllElseInvulnerable(CShip& ship) {

  for (auto &sShip : sShips)
    if ((sShip)->IsAlive() && sShip != &ship &&
        !(sShip)->IsEffectOn(CInvulnerable::GetID()))
      return false;

  return true; //yep, eb else's invulnerable, and we're not
}
