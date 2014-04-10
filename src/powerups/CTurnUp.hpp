#ifndef CTURN_UP_H
#define CTURN_UP_H


#include "CShipEffect.hpp"


class CTurnUp:public CShipEffect {

public:

  CTurnUp(const CTeam &team, CShip& ship, CLevel& level);

  virtual void Affect() override {}
  virtual void AtJustFinished() override {}
  virtual void AtStart() override {}
  static  int  GetID() { return sID; }
  
  
private:
  
 static int sID; //id in the factory
  

};


#endif
