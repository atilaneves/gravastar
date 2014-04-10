#ifndef CCOOLANT_H
#define CCOOLANT_H


#include "CShipEffect.hpp"


class CCoolant:public CShipEffect {

public:

 CCoolant(const CTeam &team, CShip& ship, CLevel& level);

 virtual void Affect() override {}
 virtual void AtJustFinished() override {}
 virtual void AtStart() override {}
 static  int  GetID() { return sID; }


private:

 static int sID; //id in the factory


};


#endif
