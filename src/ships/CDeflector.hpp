#ifndef CDEFLECTOR_H
#define CDEFLECTOR_H


#include "CFollower.hpp"


class CDeflector: public CFollower {

 public:
   CDeflector(const CSpriteVector &sprites, CLevel &level, CMoverObj &mover,
              CSound *sound = nullptr, const CVector2 &offset = CVector2(0, 0));

  virtual void Move(float dt) override;
  virtual void Hit(CSpriteObj &obj, CScreenPos pos, float dt) override;
  virtual void Hit(CProjectile &proj, CScreenPos pos, float dt) override;

 private:


  float GetVelNorm(const CProjectile& proj, bool grav) const;
  float GetThetaPrime(const CProjectile& proj, const CScreenPos& pos,
                      bool grav) const;

};


#endif
