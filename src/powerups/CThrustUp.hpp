#ifndef CTHRUST_UP_H
#define CTHRUST_UP_H


#include "CShipEffect.hpp"


class CThrustUp:public CShipEffect {

public:

  CThrustUp(const CTeam &team, CShip& ship, CLevel& level);


  virtual void Affect() { }
  virtual void AtJustFinished() { }
  virtual void AtStart() { }
  static  int  GetID() { return sID; }


private:

 static int sID; //id in the factory


};


#endif
