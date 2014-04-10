#ifndef CONESPRITEOBJ_H
#define CONESPRITEOBJ_H


#include "CSpriteObj.hpp"
#include "CGravSprite.hpp"
#include <memory>


class COneSpriteObj: public CSpriteObj {

public:

  COneSpriteObj(CLevel &level, const CVector2 &pos, CGravSprite *sprite);

  virtual const CGravSprite& GetSprite() const;


private:

  std::unique_ptr<CGravSprite> mSprite;

};


#endif
