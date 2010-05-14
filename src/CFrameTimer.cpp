#include "CFrameTimer.hpp"
#include <allegro.h>


TIMER_EQUALS() //defines update func and counter variable

static int frequency = 100;


CFrameTimer::CFrameTimer():
  CTimer(frequency, update, &counter) { 

}


CFrameTimer& CFrameTimer::Instance() {
  static CFrameTimer frameTimer;
  return frameTimer;
}

