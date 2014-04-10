#ifndef CGAME_TIMER_H
#define CGAME_TIMER_H


#include "CTimer.hpp"


class CGameTimer:public CTimer {

public:

 static CGameTimer& Instance(int bps=100) { 
  if(!sGameTimer) sGameTimer=new CGameTimer(bps); return *sGameTimer; }
 static void Delete() { delete sGameTimer;
   sGameTimer = nullptr;
 }

 int  GetCounter();


private:

 enum { kCounterIndex=0,kRate=1 };

 static CGameTimer *sGameTimer;

 ~CGameTimer();
 CGameTimer(int bps);
 CGameTimer(const CGameTimer&);

};


#endif
