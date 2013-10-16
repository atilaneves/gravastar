#ifndef CSUPER_H
#define CSUPER_H


#include "CTimeCounter.hpp"
#include "CSpriteVector.hpp"
#include "CSound.hpp"
class CShipBluePrint;
class CShip;
class CPilotInput;
class CLevel;
class CCanvas;
class CGravSprite;


class CSuper {

public:

    CSuper(const CShipBluePrint &bluePrint, CLevel &level, CShip &ship);

    void  AddGauge(float amount);
    void  ApplyInput(const CPilotInput& input);
    bool  CanUse() const { return mGauge >= 1; }
    void  DrawStats(CCanvas &canvas) const;
    float GetGauge() const { return mGauge; }
    bool  IsActive() { return mSuperCounter.IsActive() ||
            mExpCounter.IsActive(); }
    void  SetGauge(float amount) { mGauge = amount; }
    void  Update(float dt);


private:

    CLevel&       mLevel;
    CShip&        mShip;
    CTimeCounter  mExpCounter, mSuperCounter;
    const CSpriteVector& mExpSprites;
    CSound        mSound, mExpSound;
    int           mRate;
    float         mDuration;
    float         mGauge;
    const CGravSprite&  mSprite;

};


#endif
