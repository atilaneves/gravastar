#ifndef CSPECIAL_H
#define CSPECIAL_H


#include "CSound.hpp"
#include "CVector2.hpp"
class CShip;
class CShipBluePrint;
class CPilotInput;
class CShipStatSprite;
class CCanvas;
class CPilot;
class CGravSprite;
class CMoverObj;
class CTeam;


class CSpecial { //special weapon

public:

  CSpecial(const CShipBluePrint &bluePrint, CShip& ship);
  virtual ~CSpecial() { }
  
  virtual const CGravSprite& GetSprite() const = 0;

          void  ApplyInput(const CPilotInput& input);
          bool  CanUse()  const;
          float GetDepletion() const { return mDepletion; }
  virtual void  DrawStats(CCanvas &canvas) const  = 0;
          float GetGauge()    const { return mGauge;    }
          float GetMaxGauge() const { return mMaxGauge; }
  virtual bool  IsActive() const = 0;
          bool  IsAtMax()     const { return mGauge >= mMaxGauge; }
          void  LoseGauge(float amount);
  virtual void  NotUsing() = 0;
  virtual void  PlaySound() = 0;
          void  Update(float dt);
  virtual CMoverObj* UseAt(const CVector2& pos, const CVector2& vel,
			   const std::string &name, bool shadow = false)=0;


protected:

  CShip& mShip;
  const CTeam& mTeam;
  int    mRate;
  float  mMaxGauge, mGauge, mDepletion, mRecovery;


private:

  bool   mUsing;
  CSound mRepairSound;

  virtual float GetDepletionScale(float dt) const = 0;

};


#endif
