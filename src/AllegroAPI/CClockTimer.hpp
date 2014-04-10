#ifndef CCLOCK_TIMER_H
#define CCLOCK_TIMER_H


#include "CTimer.hpp"


class CClockTimer: public CTimer {

public:

  static CClockTimer& Instance();
         bool         IsReady() { return CTimer::IsReady(kCounterIndex,
                                                         kRate); }
  void Pause(int counterIndex = 0);
  void Unpause(int counterIndex = 0);



private:

  enum { kCounterIndex=0, kRate=1 };

  CClockTimer();
  CClockTimer(const CClockTimer& timer);
  CClockTimer& operator=(const CClockTimer& timer);

};


#endif
