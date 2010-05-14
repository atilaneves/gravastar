#include "CWeaponTimer.hpp"
#include "CMelee.hpp"
#include <allegro.h>


TIMER_MELEE_COUNTERS()


CWeaponTimer::CWeaponTimer(int bps):
   CTimer(bps,update,counters,CMelee::kMaxNbPilots) {

}
