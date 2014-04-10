#include "CCoolant.hpp"
#include "CEffectFactory.hpp"


REG_EFFECT(CCoolant) //register w/ the factory


static float duration = 9;
CCoolant::CCoolant(const CTeam &team, CShip& ship, CLevel& level):
   CShipEffect(level, ship, duration) {


}


