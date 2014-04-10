#ifndef CTURN_UP_H
#define CTURN_UP_H


#include "CShipEffect.hpp"


class CTurnUp:public CShipEffect {

public:

  CTurnUp(const CTeam &team, CShip& ship, CLevel& level);

  
  virtual void Affect() { }
  virtual void AtJustFinished() { }
  virtual void AtStart() { }
  static  int  GetID() { return sID; }
  
  
private:
  
 static int sID; //id in the factory
  

};


#endif
