#include "CInvulnerable.hpp"
#include "CEffectFactory.hpp"
#include "CShip.hpp"


REG_EFFECT(CInvulnerable) //register w/ the factory


static float gDuration = 3;
CInvulnerable::CInvulnerable(const CTeam &team, CShip& ship, CLevel& level):
  CFlickerEffect(team, ship, level, gDuration, ship.mInvSprites) {

}
