#ifndef CEFFECT_FACTORY_H
#define CEFFECT_FACTORY_H


#include "CIndexFactory.hpp"
class CShipEffect;
class CTeam;


typedef CShipEffect* (*createEffect_t)(const CTeam&, CShip&, CLevel&);
typedef CIndexFactory<CShipEffect, const CTeam&, CShip&, CLevel&> CEffectFactory;

#define REG_EFFECT(cname) static CShipEffect *CreateEffect(const CTeam &t,\
                                                           CShip& s,\
                                                           CLevel &l)\
 { return new cname(t, s, l); } \
 int cname::sID=\
 CEffectFactory::Instance().Register(CreateEffect);


#endif
