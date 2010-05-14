#include "CSpecialTimer.hpp"
#include "CMelee.hpp"
#include <allegro.h>


TIMER_MELEE_COUNTERS()


CSpecialTimer::CSpecialTimer(int bps):
   CTimer(bps, update, counters, CMelee::kMaxNbPilots) {

}
