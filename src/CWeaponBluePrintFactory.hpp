#ifndef CWEAPON_BLUEPRINT_FACTORY_H
#define CWEAPON_BLUEPRINT_FACTORY_H

#include "CFactory.hpp"
#include "CProjBluePrint.hpp"
#include <string>
class CTeam;


typedef CProjBluePrint* (*CreateWeaponBluePrintCB)(const CTeam&);
typedef CFactory<CProjBluePrint, std::string,
                 const CTeam&> CWeaponBluePrintFactory;

std::string getWeaponName(const std::string& name);
std::string getExtraWeaponName(const std::string& name);

#define REG_WEAPON_BLUEPRINT(shipName, projName) \
static CProjBluePrint* CreateWeaponBluePrint(const CTeam& team)\
  { return new CProjBluePrint(projName, team); } \
static const std::string __name = getWeaponName(shipName);  \
static const bool regWeaponBluePrint=\
  CWeaponBluePrintFactory::Instance().Register(__name, \
                                               CreateWeaponBluePrint);

#define REG_EXTRA_BLUEPRINT(shipName, projName) \
static CProjBluePrint* CreateExtraBluePrint(const CTeam& team)\
  { return new CProjBluePrint(projName, team); } \
static const std::string ___name = getExtraWeaponName(shipName);  \
static const bool regExtraBluePrint=\
  CWeaponBluePrintFactory::Instance().Register(___name, \
                                               CreateExtraBluePrint);

#endif
