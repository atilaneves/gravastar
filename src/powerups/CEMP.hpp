#ifndef CEMP_H
#define CEMP_H


#include "CFlickerEffect.hpp"


class CEMP : public CFlickerEffect {

public:

 CEMP(const CTeam &team, CShip& ship, CLevel &level);

  virtual void Affect()  { }
  static  int  GetID() { return sID; }
  

private:

  static int sID; //id in the factory


};


#endif
