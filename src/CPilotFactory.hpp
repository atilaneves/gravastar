#ifndef CPILOT_FACTORY_H
#define CPILOT_FACTORY_H


#include "CFactory.hpp"
#include "CPilot.hpp"
#include <string>


typedef CPilot* (*CreatePilotCB)(const CPilotOptions&, const CShipYard&,
				 CMeleeScore&);
typedef CFactory<CPilot, std::string, CreatePilotCB,
		 const CPilotOptions&, const CShipYard&,
		 CMeleeScore&> CPilotFactory;

#define REG_PILOT(type, cname) static CPilot* CreatePilot(\
 const CPilotOptions& op, const CShipYard& sy,CMeleeScore &ms) \
 { return new cname(op, sy, ms); } \
 static const bool regPilot=\
 CPilotFactory::Instance().Register(type, CreatePilot);

#endif
