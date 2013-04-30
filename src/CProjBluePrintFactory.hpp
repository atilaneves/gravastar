#ifndef CPROJ_BLUEPRINT_FACTORY_H
#define CPROJ_BLUEPRINT_FACTORY_H

#include "CFactory.hpp"
#include "CProjBluePrint.hpp"
#include <string>
class CTeam;


typedef CProjBluePrint* (*CreateProjBluePrintCB)(const CTeam&);
typedef CFactory<CProjBluePrint, std::string,
                 const CTeam&> CProjBluePrintFactory;

#define REG_PROJ_BLUEPRINT(shipName, projName) \
static CProjBluePrint* CreateProjBluePrint(const CTeam& team)\
  { return new CProjBluePrint(projName, team); } \
static const bool regProjBluePrint=\
  CProjBluePrintFactory::Instance().Register(shipName, CreateProjBluePrint);

#endif
