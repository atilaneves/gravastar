#include "CTurnUp.hpp"
#include "CEffectFactory.hpp"


REG_EFFECT(CTurnUp) //register w/ the factory

static float duration = 15;
CTurnUp::CTurnUp(const CTeam &team, CShip& ship, CLevel& level):
   CShipEffect(level, ship, duration) {


}
