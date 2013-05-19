#ifndef CSUPERBEAM_H
#define CSUPERBEAM_H


#include "CWeaponFollow.hpp"
class CPulseLaser;


class CSuperBeam: public CWeaponFollow {

 public:

  CSuperBeam(const CSpriteVector &sprites, CLevel &level, CShip &ship,
             CPulseLaser *pulseLaser = 0);

  virtual CLevelSprite Draw() override;
  virtual void Erase() override;
          int  GetNose() const;
  virtual bool IsActive() override;
  virtual void Move(float dt) override;


 private:

  CPulseLaser *mPulseLaser;
  CVector2 mStartPos;
  std::vector<CScreenPos> GetPositions();

};


#endif
