#ifndef CFRAME_TIMER_H
#define CFRAME_TIMER_H


#include "CTimer.hpp"


class CFrameTimer: public CTimer {

public:

  static CFrameTimer& Instance();
         bool         IsReady() { return CTimer::IsReady(kCounterIndex,
                                                         kRate); }


private:

  enum { kCounterIndex=0, kRate=1 };

  CFrameTimer();
  CFrameTimer(const CFrameTimer& timer);
  CFrameTimer& operator=(const CFrameTimer& timer);

};


#endif
