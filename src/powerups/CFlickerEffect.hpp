#ifndef CFLICKEREFFECT_H
#define CFLICKEREFFECT_H


#include "CShipEffect.hpp"
#include "CSpriteVector.hpp"
class CFlicker;


//class of effects that have a flicker effect to indicate their presence

class CFlickerEffect : public CShipEffect {

public:

  CFlickerEffect(const CTeam &team, CShip& ship, CLevel &level,
                 float duration, const CSpriteVector& sprites);

  virtual void AtStart();
  virtual void AtJustFinished();


private:

  const CSpriteVector& mSprites;
  CFlicker *mFlicker;

};


#endif
