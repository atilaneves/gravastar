#ifndef CFOLLOWER_H
#define CFOLLOWER_H


#include "CMoverObj.hpp"
#include "CSound.hpp"
#include <memory>


class CFollower: public CMoverObj {

public:

  CFollower(const CSpriteVector &sprites, CLevel &level, CMoverObj &mover,
            CSound *sound = 0, const CVector2& offset = CVector2(0, 0));
  virtual ~CFollower();

  virtual CVector2 CalcAcc() { return CVector2(0, 0); }
  virtual void     Die() { mActive = false; }
  virtual int      GetSpriteIndex() const { return mSpriteIndex; }
  virtual bool     IsActive()  { return mActive && mFollowed.IsAlive(); }
  virtual void     Move(float dt);
  virtual void     OutOfBounds(float dt) { }


protected:

  bool                    mActive;
  int                     mSpriteIndex;
  CMoverObj&              mFollowed;
  std::unique_ptr<CSound> mSound;
  CVector2                mOffset;

};


#endif
