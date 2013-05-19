#ifndef CENGINE_H
#define CENGINE_H


class CPilotInput;
class CShipBluePrint;
class CLevel;
class CShip;
class CSpriteVector;
class CFlicker;
#include "CSound.hpp"
#include "CVector2.hpp"
#include "CSpriteObj.hpp"


class CEngine {

public:

  CEngine(const CShipBluePrint &bluePrint, CLevel &level, CShip &ship);

  void     ApplyInput(const CPilotInput &controls);
  CVector2 CalcAcc(float angle) const;
  bool     IsOn() const { return mOn; }
  void     Reset();


private:

  bool                 mOn;
  const float          mThrust, mMaxVel;
  CFlicker*            mExaust;
  CLevel&              mLevel;
  CShip&               mShip;
  const CSpriteVector& mExaustSprites;
  CSound               mSound;

  void  ExaustOff();
  void  ExaustOn();
  float GetMaxVel() const;
  float GetThrust() const;
  float SpeedFactor(const CVector2 &acc, const CVector2 &vel) const;


};


#endif
