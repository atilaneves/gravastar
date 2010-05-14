#ifndef CSPECIAL_FACTORY_H
#define CSPECIAL_FACTORY_H


#include "CSpecial.hpp"
#include "CFactory.hpp"
#include <string>
class CShipBluePrint;
class CShip;
class CLevel;


typedef CSpecial* (*CreateSpecialCB)(const CShipBluePrint&, CShip&, CLevel&);
typedef CFactory<CSpecial, std::string, CreateSpecialCB,
		 const CShipBluePrint&, CShip&, CLevel&> CSpecialFactory;

#define REG_SPECIAL(sname,cname) static CSpecial *CreateSpecial(\
 const CShipBluePrint &bp, CShip& sh, CLevel &lv)\
 { return new cname(bp, sh, lv); } \
 static const bool regSpecial=\
 CSpecialFactory::Instance().Register(sname, CreateSpecial);

#endif
