#ifndef CABSORBER_H
#define CABSORBER_H


#include "CFollower.hpp"


class CAbsorber: public CFollower {

 public:

  CAbsorber(const CSpriteVector &sprites, CLevel &level, CMoverObj &mover,
	    CSound *sound = 0, const CVector2& offset = CVector2(0, 0));

  virtual void Hit(CSpriteObj&   obj, CScreenPos pos, float dt);
  virtual void Hit(CProjectile& proj, CScreenPos pos, float dt);
  virtual void Move(float dt);

 private:


};


#endif
