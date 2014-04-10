#ifndef CTIMECOUNTER_H
#define CTIMECOUNTER_H



class CTimeCounter {

public:

  CTimeCounter();
  
  bool  IsActive();
  bool  JustFinished();
  void  Pause();
  void  Reset();
  void  Start(double seconds = 0);
  float TimeLeft();
  void  Unpause();


private:
  
  bool mEnded;
  int  mStart;
  int  mLength;
  int  mPauseTime;
  


};


#endif
