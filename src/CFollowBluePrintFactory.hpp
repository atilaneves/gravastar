#ifndef CFOLLOW_BLUEPRINT_FACTORY_H
#define CFOLLOW_BLUEPRINT_FACTORY_H

#include "CFactory.hpp"
#include "CFollowBluePrint.hpp"
#include "CFollowSpecial.hpp"
#include <string>
class CTeam;


typedef CFollowBluePrint* (*CreateFollowBluePrintCB)(const CTeam&);
typedef CFactory<CFollowBluePrint, std::string,
                 const CTeam&> CFollowBluePrintFactory;

std::string getFollowName(const std::string& name);
std::string getExtraFollowName(const std::string& name);


#define REG_FOLLOW_BLUEPRINT(shipName, followName) \
static CFollowBluePrint* CreateFollowBP(const CTeam& team)\
  { return new CFollowBluePrint(followName, team); } \
static const bool regFollowBluePrint=\
  CFollowBluePrintFactory::Instance().Register(getFollowName(shipName),\
                                               CreateFollowBP);

#define REG_EXTRA_FOLLOW_BLUEPRINT(shipName, followName) \
static CFollowBluePrint* CreateExtraFollowBP(const CTeam& team)\
  { return new CFollowBluePrint(followName, team); } \
static const bool regExtraFollowBluePrint=\
  CFollowBluePrintFactory::Instance().Register(getExtraFollowName(shipName),\
                                               CreateExtraFollowBP);


#endif
