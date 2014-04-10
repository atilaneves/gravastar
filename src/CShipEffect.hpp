#ifndef CSHIP_EFFECT_H
#define CSHIP_EFFECT_H


class CShip;
class CDataFile;
class CSound;
class CSpriteObj;
class CLevel;
class CTeam;
#include "CTimeCounter.hpp"
#include <vector>


class CShipEffect {

public:

 CShipEffect(CLevel &level, CShip &ship, float duration);
  virtual ~CShipEffect() { }

  virtual void Affect() = 0;
  virtual void AtJustFinished() = 0;
  virtual void AtStart() = 0;
          bool IsActive()     { return mCounter.IsActive();     }
          bool JustFinished() { return mCounter.JustFinished(); }
          void Pause() { mCounter.Pause(); }
          void Reset();
          void Start(float duration = -1);
          void Unpause() { mCounter.Unpause(); }
          void Update();
  virtual bool WorksOnDeadShip() const { return false; }


protected:

  CLevel&     mLevel;
  CShip&      mShip;


private:

 float        mDuration; //how long the effect lasts
 CTimeCounter mCounter;  //keeps the time

};



#endif
