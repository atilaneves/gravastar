#ifndef CEMB_H
#define CEMB_H


#include "CFlickerEffect.hpp"


class CEMB : public CFlickerEffect {

public:

 CEMB(const CTeam &team, CShip& ship, CLevel &level);

 virtual void Affect() override {}
  static  int  GetID() { return sID; }
  

private:

  static int sID; //id in the factory

};


#endif
