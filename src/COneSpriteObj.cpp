#include "COneSpriteObj.hpp"


COneSpriteObj::COneSpriteObj(CLevel &level, const CVector2 &pos,
			     CGravSprite *sprite):
  CSpriteObj(level, pos), mSprite(sprite) { 

}


const CGravSprite& COneSpriteObj::GetSprite() const { 
  return *mSprite; 
}
