#ifndef CLIGHTNING_H
#define CLIGHTNING_H


#include "CWeaponFollow.hpp"


class CLightning: public CWeaponFollow {

 public:

  CLightning(const CSpriteVector &sprites, CLevel &level, CMoverObj &mover,
	    CSound *sound = 0, const CVector2& offset = CVector2(0, 0));

  virtual void Move(float dt);


 private:

};


#endif
