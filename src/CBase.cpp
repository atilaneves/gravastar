#include "CBase.hpp"
#include "CCanvas.hpp"
#include "CColour.hpp"
#include "CLevel.hpp"
#include "CShip.hpp"
#include "CShips.hpp"


CBase::CBase(CLevel &level, const CVector2 &pos, CGravSprite *sprite,
	     const CSound &klang):
  CIndestructible(level, pos, sprite, klang),
  mCanvas(level.GetCanvas()) {
  CCanvas canvas(1, 30);
  canvas.Clear(CColour::GetWhite());
  mSprite.reset(new CGravSprite(canvas.GetData()));
}


CVector2 CBase::GetFreePos(const CGravSprite& sprite) const {
  CVector2 pos = GetPos();
  CVector2 deltaS = CVector2(1.5 * M_PI) * 1.5;
  while(sprite.Collided(mCanvas, GetSprite(), pos, GetPos()))
    pos += deltaS;

  positions_t collisions = sprite.Collided(mCanvas, pos);
  return collisions.size() == 0 ? pos : CVector2(-1, -1);
}


void CBase::ShipLanded(CShip &ship, float dt) {
  ship.Repair(dt);
}
