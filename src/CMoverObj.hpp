#ifndef CMOVEROBJ_H
#define CMOVEROBJ_H


#include "CSpriteObj.hpp"
#include "CSpriteVector.hpp"
class CLevel;


class CMoverObj: public CSpriteObj {

public:

  CMoverObj(const CSpriteVector &sprites, CLevel &level,
	    const CVector2 &pos, const CVector2 &vel);

  virtual CVector2     CalcAcc() = 0;
  virtual void         Die() = 0;
  virtual const CGravSprite& GetSprite() const {
    return *(mSprites[GetSpriteIndex()]); }
  virtual int          GetSpriteIndex() const = 0;
  const   CVector2&    GetVel() const { return mVel; }
  virtual bool         IsAlive() { return IsActive(); }
  virtual void         Move(float dt);
          void         SetVel(const CVector2& v) { mVel = v; }
  virtual void         Update(float dt);


protected:

  const CSpriteVector& mSprites;
  CVector2             mVel;


private:

          void KeepInBounds();
  virtual void OutOfBounds(float angle) = 0;


};


#endif
