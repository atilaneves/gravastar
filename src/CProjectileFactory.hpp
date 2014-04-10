#ifndef CPROJECTILE_FACTORY_H
#define CPROJECTILE_FACTORY_H


#include "CFactory.hpp"
#include "CVector2.hpp"
#include "CProjectile.hpp"
#include <string>
class CProjBluePrint;
class CShip;


typedef CProjectile* (*CreateProjCB)(const CProjBluePrint&, 
                                     CShip&, const CVector2&,
                                     const CVector2&, bool);

typedef CFactory<CProjectile, std::string,
                 const CProjBluePrint&, CShip&,
                 const CVector2&, const CVector2&, bool> CProjectileFactory;


#define REG_PROJECTILE(pname, cname) static CProjectile* CreateProjectile(\
 const CProjBluePrint &bp, CShip &shp, const CVector2& ps, \
 const CVector2& vl, bool sh = false) \
 { return new cname(bp, shp, ps, vl, sh); } \
 static const bool regProjectile =\
 CProjectileFactory::Instance().Register(pname, CreateProjectile);

//2nd macro so both can be used in the same cpp file
#define REG_WEAPON_PROJ(pname, cname) static CProjectile* CreateWeaponProj(\
 const CProjBluePrint &bp, CShip &shp, const CVector2& ps, \
 const CVector2& vl, bool sh = false) \
 { return new cname(bp, shp, ps, vl, sh); } \
 static const bool regWeaponProj =\
 CProjectileFactory::Instance().Register(pname, CreateWeaponProj);



#endif
