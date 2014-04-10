#include "CClock.hpp"
#include "CClockTimer.hpp"


clock_t CClock::sClock = 0;


void CClock::Reset() { //start again
  CClockTimer::Instance().Reset();
  sClock = CClockTimer::Instance().GetCounter();
}


float CClock::DeltaS() { //delta t in s
  return DeltaMS() / float(CClockTimer::Instance().GetFrequency());
}


int CClock::DeltaMS() { //delta t in ms
  clock_t now = CClockTimer::Instance().GetCounter();
  clock_t diff = (now - sClock);
  sClock = now;
  return diff;
}
