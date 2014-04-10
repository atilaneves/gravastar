#ifndef CTHRUST_UP_H
#define CTHRUST_UP_H


#include "CShipEffect.hpp"


class CThrustUp:public CShipEffect {

public:

  CThrustUp(const CTeam &team, CShip& ship, CLevel& level);

  virtual void Affect() override {}
  virtual void AtJustFinished() override {}
  virtual void AtStart() override {}
  static  int  GetID() { return sID; }


private:

 static int sID; //id in the factory


};


#endif
