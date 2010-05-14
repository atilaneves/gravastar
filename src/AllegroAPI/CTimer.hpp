#ifndef TIMER_H
#define TIMER_H


typedef void (*timerFunction_t)();


class CTimer {

public:
 
  bool IsReady(int counterIndex = 0, int rate = 0);
  int  GetCounter(int counterIndex = 0);
  int  GetFrequency() const { return mFrequency; }
  void Reset(int counterIndex = 0);
  void Pause(int counterIndex = 0);
  void Unpause(int counterIndex = 0);


protected:

 CTimer(int bps, timerFunction_t function,
	volatile int *counters, int nbCounters = 1);
 ~CTimer();


private:

  enum {kMaxNbCounters = 100};

  int mFrequency;
  int mNbCounters;
  int mPause[kMaxNbCounters];
  volatile int *mCounters;  //counters to be updated
  timerFunction_t mFunction;

};


#define TIMER_EQUALS() static volatile int counter=0; \
 static void update() { \
 counter=1; \
 } \
 END_OF_FUNCTION(update)

#define TIMER_INC() static volatile int counter=0; \
 static bool paused=false; \
 static void update() { \
  if(!paused) counter++; \
 } \
 END_OF_FUNCTION(update) \

#define TIMER_MELEE_COUNTERS() static volatile int \
 counters[CMelee::kMaxNbPilots]={0,0,0,0}; \
 static void update() { \
 for(int p=0; p<CMelee::kMaxNbPilots; p++) \
    counters[p]++; \
 } \
 END_OF_FUNCTION(update)


#endif
