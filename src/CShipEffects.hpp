#ifndef CSHIPEFFECTS_H
#define CSHIPEFFECTS_H


class CShip;
class CTeam;
#include "CShipEffect.hpp"
#include "CTimeCounter.hpp"
#include <vector>


class CShipEffects {

public:

  CShipEffects(const CTeam& team, CShip& ship, CLevel &level);
  ~CShipEffects();
  
  CShipEffect *GetEffect(int i) { return mEffects[i]; }
  bool IsActive(int i)     { return mEffects[i]->IsActive(); }
  bool JustFinished(int i) { return mEffects[i]->JustFinished(); }
  void Pause(float t = 1e9);
  void Reset();
  void Reset(int i) { mEffects[i]->Reset(); }
  void Start(int i, float d = -1) { mEffects[i]->Start(d); }
  void Unpause();
  void Update();

  

private:

 std::vector<CShipEffect*> mEffects;
  CTimeCounter mPauseCounter;

};



#endif
