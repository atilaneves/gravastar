#ifndef CSHIPAURA_H
#define CSHIPAURA_H


class CLevel;
class CShip;
class CShipBluePrint;
class CFlicker;
#include "CSpriteObj.hpp"
#include "CSpriteVector.hpp"
#include "CSound.hpp"
#include <memory>


class CShipAura {

public:

  CShipAura(CLevel& level, CShip& ship, const CShipBluePrint &bluePrint);

  float GetBaseHull()    const { return mBaseHull;    }
  float GetBaseSpecial() const { return mBaseSpecial; }
  void  Play();
  void  Repair(float dt);
  void  Update();


private:

  bool            mRepairing;
  float           mBaseHull, mBaseSpecial;
  CLevel&         mLevel;
  CShip&          mShip;
  CSpriteVector   mSprites;
  CSound          mSound;
  CFlicker*       mAura;

};


#endif
