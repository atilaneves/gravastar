#include "CGameTimer.hpp"
#include <allegro.h>


TIMER_INC()
CGameTimer *CGameTimer::sGameTimer = nullptr;

CGameTimer::CGameTimer(int bps):
   CTimer(bps,update,&counter) {


}


CGameTimer::~CGameTimer() {

}


int CGameTimer::GetCounter() {
 return counter;
}


