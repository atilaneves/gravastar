#ifndef CSHIP_FACTORY_H
#define CSHIP_FACTORY_H


#include "CWeaponBluePrintFactory.hpp"
#include "CProjSpecialFactory.hpp"
#include "CFollowSpecialFactory.hpp"
#include <string>


typedef CShip* (*CreateShipCB)(const CShipBluePrint&, CPilot&, CLevel&);


typedef CFactory<CShip, std::string,
                 const CShipBluePrint&, CPilot&, CLevel&> CShipFactory;

#define REG_SHIP(sname, cname) static CShip* CreateShip(\
 const CShipBluePrint &bp, CPilot &pl, CLevel &lv) \
 { return new cname(bp, pl, lv); } \
 static const bool regShip =\
 CShipFactory::Instance().Register(sname, CreateShip);

#define REG_PROJ_SHIP(shipName, className, weapName, specName, \
                      projClass, specialClass) \
 REG_SHIP(shipName, className) \
 REG_WEAPON_BLUEPRINT(shipName, weapName) \
 REG_PROJ_SPECIAL(shipName, specialClass, specName, projClass)

#define REG_FOLLOW_SHIP(shipName, className, weapName, specName, \
                        projClass, specialClass) \
 REG_SHIP(shipName, className) \
 REG_WEAPON_BLUEPRINT(shipName, weapName) \
 REG_FOLLOW_SPECIAL(shipName, specialClass, specName, projClass)


#endif
