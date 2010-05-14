#ifndef CCOOLANT_H
#define CCOOLANT_H


#include "CShipEffect.hpp"


class CCoolant:public CShipEffect {

public:

 CCoolant(const CTeam &team, CShip& ship, CLevel& level);

 virtual void Affect() { }
 virtual void AtJustFinished() { }
 virtual void AtStart() { }
 static  int  GetID() { return sID; }


private:

 static int sID; //id in the factory


};


#endif
