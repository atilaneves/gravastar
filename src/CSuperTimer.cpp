#include "CSuperTimer.hpp"
#include "CMelee.hpp"
#include <allegro.h>


TIMER_MELEE_COUNTERS()



CSuperTimer::CSuperTimer(int bps):
   CTimer(bps,update,counters,CMelee::kMaxNbPilots) {

}
