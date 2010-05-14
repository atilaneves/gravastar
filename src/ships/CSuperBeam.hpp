#ifndef CSUPERBEAM_H
#define CSUPERBEAM_H


#include "CWeaponFollow.hpp"
class CPulseLaser;


class CSuperBeam: public CWeaponFollow {

 public:

  CSuperBeam(const CSpriteVector &sprites, CLevel &level, CShip &ship,
	     CPulseLaser *pulseLaser = 0);

  virtual void Draw();
  virtual void Erase();
          int  GetNose() const;
  virtual bool IsActive();
  virtual void Move(float dt);


 private:

  CPulseLaser *mPulseLaser;
  CVector2 mStartPos;
  std::vector<CScreenPos> GetPositions();

};


#endif
