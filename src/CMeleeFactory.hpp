#ifndef CMELEE_FACTORY_H
#define CMELEE_FACTORY_H

#include "CFactory.hpp"
#include "CMelee.hpp"
#include "CGravOptions.hpp"
#include <string>

typedef CMelee* (*CreateMeleeCB)(const CGravOptions&);
typedef CFactory<CMelee, std::string, CreateMeleeCB,
                 const CGravOptions&> CMeleeFactory;

#define REG_MELEE(type,cname) static CMelee *CreateMelee(\
 const CGravOptions &o)\
 { return new cname(o); } \
 static const bool regMelee=\
 CMeleeFactory::Instance().Register(type, CreateMelee);

#define REG_MELEE2(type,cname) static CMelee *CreateMelee2(\
 const CGravOptions &o)\
 { return new cname(o); } \
 static const bool regMelee2=\
 CMeleeFactory::Instance().Register(type, CreateMelee2);


#endif
