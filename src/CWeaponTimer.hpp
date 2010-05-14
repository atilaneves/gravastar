#ifndef CWEAPONTIMER_H
#define CWEAPONTIMER_H


#include "CTimer.hpp"


class CWeaponTimer:public CTimer {

public:

 static CWeaponTimer& Instance(int bps=20)
  { static CWeaponTimer weaponTimer(bps); 
    return weaponTimer; }


private:

  static CWeaponTimer sWeaponTimer;
  CWeaponTimer(int bps);
  CWeaponTimer(const CWeaponTimer&);

};

#endif
