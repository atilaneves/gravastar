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
    for(unsigned int i = 0; i < mEffects.size(); i++)
        delete mEffects[i];
}


void CShipEffects::Reset() { 
    for(unsigned int i=0; i<mEffects.size(); i++)
        mEffects[i]->Reset();
}


void CShipEffects::Update() {
    bool unpause = mPauseCounter.JustFinished();
    for(unsigned int i=0; i<mEffects.size(); i++) {
        mEffects[i]->Update();
        if(unpause) mEffects[i]->Unpause();
    }
}


void CShipEffects::Pause(float t) {
    mPauseCounter.Start(t);
    for(unsigned int i=0; i<mEffects.size(); i++)
        mEffects[i]->Pause();
}


void CShipEffects::Unpause() {
    for(unsigned int i=0; i<mEffects.size(); i++)
        mEffects[i]->Unpause();
}
