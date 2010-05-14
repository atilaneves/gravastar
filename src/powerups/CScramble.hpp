#ifndef CSCRAMBLE_H
#define CSCRAMBLE_H


#include "CFlickerEffect.hpp"


class CScramble:public CFlickerEffect {
  
public:
  
  CScramble(const CTeam &team, CShip& ship, CLevel& level);
  
  virtual void Affect();
  static  int  GetID() { return sID; }


private:

  static int sID; //id in the factory

};


#endif
