#include "CThrustUp.hpp"
#include "CEffectFactory.hpp"


REG_EFFECT(CThrustUp) //register w/ the factory

static float duration = 9;
CThrustUp::CThrustUp(const CTeam &team, CShip& ship, CLevel& level):
   CShipEffect(level, ship, duration) {


}
