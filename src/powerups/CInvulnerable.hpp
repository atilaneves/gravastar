#ifndef CINVULNERABLE_H
#define CINVULNERABLE_H


#include "CFlickerEffect.hpp"


class CInvulnerable : public CFlickerEffect {

public:

 CInvulnerable(const CTeam &team, CShip& ship, CLevel &level);

 virtual void Affect() override {}
  static  int  GetID() { return sID; }
  

private:

  static int sID; //id in the factory

};


#endif
