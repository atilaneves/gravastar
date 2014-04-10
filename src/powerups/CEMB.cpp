#include "CEMB.hpp"
#include "CEffectFactory.hpp"
#include "CShip.hpp"


REG_EFFECT(CEMB) //register w/ the factory


static float gDuration = 8;
CEMB::CEMB(const CTeam &team, CShip& ship, CLevel& level):
  CFlickerEffect(team, ship, level, gDuration, ship.mEMPSprites) {

}
