#ifndef CFOLLOW_SPECIAL_FACTORY_H
#define CFOLLOW_SPECIAL_FACTORY_H


#include "CSpecialFactory.hpp"
#include "CFollowSpecial.hpp"
#include "CFollowFactory.hpp"
#include "CFollowBluePrintFactory.hpp"


#define REG_FOLLOW_SPECIAL(shipName, specialClass, followName, followClass) \
 REG_SPECIAL(shipName, specialClass) \
 REG_FOLLOW_BLUEPRINT(shipName, followName) \
 REG_FOLLOW(followName, followClass)


#endif
