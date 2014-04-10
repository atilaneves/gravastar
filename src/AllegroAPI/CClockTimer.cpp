#include "CClockTimer.hpp"
#include "CGameTimer.hpp"
#include <allegro.h>


TIMER_INC() //defines update func and counter variable

static int frequency = 2000;


CClockTimer::CClockTimer():
  CTimer(frequency, update, &counter) {

}


CClockTimer& CClockTimer::Instance() {
  static CClockTimer clockTimer;
  return clockTimer;
}



void CClockTimer::Pause(int counterIndex) {
  CTimer::Pause(counterIndex);
  CGameTimer::Instance().Pause(counterIndex);
}


void CClockTimer::Unpause(int counterIndex) {
  CTimer::Unpause(counterIndex);
  CGameTimer::Instance().Unpause(counterIndex);
}
