#include "CExplosionPause.hpp"
#include "CEffectFactory.hpp"


REG_EFFECT(CExplosionPause) //register w/ the factory


static float gDuration = 2;
CExplosionPause::CExplosionPause(const CTeam &team, CShip& ship, CLevel &level):
   CShipEffect(level, ship, gDuration) {


}
