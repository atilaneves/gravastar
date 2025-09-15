#include "CSpecialExplosion.hpp"
#include "CShip.hpp"


CSpecialExplosion::CSpecialExplosion(CLevel &level, const CVector2& pos,
                                     const CSpriteVector &sprites,
                                     const CSound &sound):
  CExplosion(level, pos, sprites, sound, kSpeed)
{

}
