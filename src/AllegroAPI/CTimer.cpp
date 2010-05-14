#include "CTimer.hpp"
#include <allegro.h>


CTimer::CTimer(int bps, timerFunction_t function,
	       volatile int *counters, int nbCounters):
  mFrequency(bps), mCounters(counters), mFunction(function) { 

 if(nbCounters == 1)
    LOCK_VARIABLE(*mCounters);
 else
    LOCK_VARIABLE(mCounters);

 LOCK_FUNCTION(mFunction);
 install_int_ex(function, BPS_TO_TIMER(mFrequency));
}


CTimer::~CTimer() {
  remove_int(mFunction);
}


bool CTimer::IsReady(int counterIndex, int rate) {
  bool ready = mCounters[counterIndex] >= rate;
  if(ready) mCounters[counterIndex] = 0; //reset
  return ready;
}


int CTimer::GetCounter(int counterIndex) {
  return mCounters[counterIndex];
}


void CTimer::Reset(int counterIndex) {
  mCounters[counterIndex] = 0;
}


void CTimer::Pause(int counterIndex) {
  mPause[counterIndex] = mCounters[counterIndex];
}


void CTimer::Unpause(int counterIndex) {
  mCounters[counterIndex] = mPause[counterIndex];
}
