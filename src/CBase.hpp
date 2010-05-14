#ifndef CBASE_H
#define CBASE_H


#include "CIndestructible.hpp"
#include "CGravSprite.hpp"
#include <memory>
class CCanvas;


class CBase: public CIndestructible {

public:

  CBase(CLevel &level, const CVector2 &pos, CGravSprite *sprite,
	const CSound& klang);

  CVector2 GetFreePos(const CGravSprite& sprite) const;


private:

  const CCanvas& mCanvas;
  std::auto_ptr<CGravSprite> mSprite;

  virtual void ShipLanded(CShip &ship, float dt);

};

#endif
