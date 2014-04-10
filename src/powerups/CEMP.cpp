#include "CEMP.hpp"
#include "CEffectFactory.hpp"
#include "CShip.hpp"


REG_EFFECT(CEMP) //register w/ the factory


static float gDuration = 3;
CEMP::CEMP(const CTeam &team, CShip& ship, CLevel& level):
  CFlickerEffect(team, ship, level, gDuration, ship.mEMPSprites) {

}
