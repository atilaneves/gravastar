#include "CShipEffects.hpp"
#include "CEffectFactory.hpp"
#include "CTeam.hpp"
#include "CShip.hpp"


CShipEffects::CShipEffects(const CTeam &team, CShip& ship, CLevel &level) {

    CEffectFactory &factory = CEffectFactory::Instance();
    for(int eff = 0; eff < factory.GetNbClasses(); eff++)
        mEffects.push_back(factory.CreateObject(eff, team, ship, level));
}


CShipEffects::~CShipEffects() {
  for (auto &elem : mEffects)
    delete elem;
}


void CShipEffects::Reset() {
  for (auto &elem : mEffects)
    elem->Reset();
}


void CShipEffects::Update() {
    bool unpause = mPauseCounter.JustFinished();
    for (auto &elem : mEffects) {
      elem->Update();
        if(unpause)
          elem->Unpause();
    }
}


void CShipEffects::Pause(float t) {
    mPauseCounter.Start(t);
    for (auto &elem : mEffects)
      elem->Pause();
}


void CShipEffects::Unpause() {
  for (auto &elem : mEffects)
    elem->Unpause();
}
