#include "CTimeCounter.hpp"
#include "CGameTimer.hpp"



CTimeCounter::CTimeCounter():
   mEnded(false), mStart(-1), mLength(0) {

}


void CTimeCounter::Start(double seconds) {
 mLength = int(seconds*CGameTimer::Instance().GetFrequency());
 mStart = CGameTimer::Instance().GetCounter();
 if(mLength == 0) mLength = 1; //updates at least once
}


bool CTimeCounter::IsActive() {
 if(mStart >= 0) {
    int counter = CGameTimer::Instance().GetCounter();
    if(counter < mStart + mLength) 
       return true;
    else {
       mEnded  = true;
       mStart  = -1;
       mLength = 0;
       return false;
    }
 }
 else
    return false;
}


bool CTimeCounter::JustFinished() {
 if(mEnded) {
    mEnded = false;
    return true;
 }
 else {
    IsActive(); //chk and set
    if(mEnded) {
       mEnded = false;
       return true;
    }
 }

 return false;
}


void CTimeCounter::Reset() {
 mStart  = 0;
 mLength = 0;
 mEnded  = false;
}


float CTimeCounter::TimeLeft() {
 int diff = mStart + mLength - CGameTimer::Instance().GetCounter();
 return diff/(float)CGameTimer::Instance().GetFrequency();
}


void CTimeCounter::Pause() {
  mPauseTime = CGameTimer::Instance().GetCounter();
}


void CTimeCounter::Unpause() {
  mStart += CGameTimer::Instance().GetCounter() - mPauseTime;
}
