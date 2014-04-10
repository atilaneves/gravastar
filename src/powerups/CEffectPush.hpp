#ifndef CEFFECT_PUSH_H
#define CEFFECT_PUSH_H


#include "CShipEffect.hpp"
class CPilot;


class CEffectPush:public CShipEffect {

public:

  CEffectPush(const CTeam &team, CShip& ship, CLevel& level);
  virtual ~CEffectPush() { }
  
  virtual void 	  Affect() { }
  virtual void 	  AtJustFinished() { }
  virtual void 	  AtStart() { }
  static  int  	  GetID() { return sID; }
          CPilot& GetPilot() const { return *mPilot; }
          void    SetPilot(CPilot &pilot) { mPilot = &pilot; }


private:

  CPilot *mPilot;
  static int sID; //id in the factory


};


#endif
