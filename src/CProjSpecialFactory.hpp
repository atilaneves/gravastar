#ifndef CPROJ_SPECIAL_FACTORY_H
#define CPROJ_SPECIAL_FACTORY_H


#include "CSpecialFactory.hpp"
#include "CProjBluePrintFactory.hpp"
#include "CProjSpecial.hpp"
#include "CProjectileFactory.hpp"


#define REG_PROJ_SPECIAL(shipName, specialClass, projName, projClass) \
 REG_SPECIAL(shipName, specialClass) \
 REG_PROJ_BLUEPRINT(shipName, projName) \
 REG_PROJECTILE(projName, projClass)


#endif
