#ifndef CSPRITEOBJ_H
#define CSPRITEOBJ_H



class CLevel;
class CShip;
class CProjectile;
#include "CGravSprite.hpp"
#include "CVector2.hpp"
#include "CScreenPos.hpp"
#include "CTimeCounter.hpp"


class CSpriteObj {

public:

  enum { kHitNothing = -1, kHitSpriteObj, kHitTerrain };

  CSpriteObj(CLevel &level, const CVector2 &pos);
  virtual ~CSpriteObj();

  	  void         CheckCollision(float dt);
  	  bool         Collided() const;
  	  bool         Collided(const CSpriteObj& obj) const;
  	  positions_t  GetCollisions() const;
  virtual void         Hit(CSpriteObj&   obj, CScreenPos pos, float dt) { }
  virtual void         Hit(CShip&       ship, CScreenPos pos, float dt) { }
  virtual void         Hit(CProjectile& proj, CScreenPos pos, float dt) { }
  virtual void         HitTerrain(const CScreenPos &where, float dt)    { }
  virtual void         Draw();
  virtual void         Erase();
  int                  GetHeight() const { return GetSprite().GetHeight(); }
  const CVector2&      GetPos()    const { return mPos; }
  virtual const CGravSprite& GetSprite() const = 0;
  int                  GetWidth()  const { return GetSprite().GetWidth(); }
  bool                 InSprite(CScreenPos pos);
  virtual bool 	       IsActive()        { return true; }
  bool                 IsStopped() { return mStoppedCounter.IsActive(); }
  bool                 IsUpdated() const { return mUpdated; }
          void         SetUpdated(bool u) { mUpdated = u; }
  virtual void         Stop(float t) {
    if(!IsStopped()) mStoppedCounter.Start(t); }
  virtual void         Update(float dt) = 0;


protected:

  CLevel&  mLevel;
  CVector2 mPos;
  bool mUpdated;
  CTimeCounter mStoppedCounter;

  int GetTopLeftX() const { return (int)mPos.GetX() - GetWidth()/2;  }
  int GetTopLeftY() const { return (int)mPos.GetY() - GetHeight()/2; }

};



#endif
