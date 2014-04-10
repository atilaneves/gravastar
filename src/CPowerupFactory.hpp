#ifndef CPOWERUP_FACTORY_H
#define CPOWERUP_FACTORY_H


#include "CPowerup.hpp"
#include "CFactory.hpp"
#include "CVector2.hpp"
class CPowerups;
#include <string>

typedef CPowerup* (*CreatePowerupCB)(CPowerups&,CLevel&, const CVector2&,
                                     const CGravSprite&);
typedef CFactory<CPowerup, std::string, CPowerups&, CLevel&, const CVector2&,
                 const CGravSprite&> CPowerupFactory;

#define REG_POWERUP(pname, cname) static CPowerup *CreatePowerup( \
                                                          CPowerups& ps, \
                                                          CLevel& l, \
                                                          const CVector2& p,\
                                                          const CGravSprite& s)\
 { return new cname(ps, l, p, s); } \
 static const bool regPowerup=\
 CPowerupFactory::Instance().Register(pname, CreatePowerup);

#endif
