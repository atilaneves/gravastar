#ifndef CEXPLOSION_PAUSE_H
#define CEXPLOSION_PAUSE_H


class CTeam;
#include "CShipEffect.hpp"


class CExplosionPause: public CShipEffect {

public:

  CExplosionPause(const CTeam &team, CShip& ship, CLevel &level);
  virtual ~CExplosionPause() { }
  
  virtual void Affect() { }
  virtual void AtJustFinished() { }
  virtual void AtStart() { }
  virtual bool WorksOnDeadShip() const { return true; }

  static  int  GetID() { return sID; }
  

private:
  
  static int sID; //id in the factory


};


#endif
