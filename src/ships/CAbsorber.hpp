#ifndef CABSORBER_H
#define CABSORBER_H


#include "CFollower.hpp"


class CAbsorber: public CFollower {

 public:
   CAbsorber(const CSpriteVector &sprites, CLevel &level, CMoverObj &mover,
             CSound *sound = nullptr, const CVector2 &offset = CVector2(0, 0));

  virtual void Hit(CSpriteObj &obj, CScreenPos pos, float dt) override;
  virtual void Hit(CProjectile &proj, CScreenPos pos, float dt) override;
  virtual void Move(float dt) override;

 private:


};


#endif
