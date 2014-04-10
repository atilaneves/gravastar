#include "CEffectPush.hpp"
#include "CEffectFactory.hpp"


REG_EFFECT(CEffectPush) //register w/ the factory


static float duration = 0.5;
CEffectPush::CEffectPush(const CTeam &team, CShip& ship, CLevel& level):
   CShipEffect(level, ship, duration) {


}
