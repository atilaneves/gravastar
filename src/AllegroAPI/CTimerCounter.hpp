#ifndef CTIMECOUNTER_H
#define CTIMECOUNTER_H



class CTimeCounter {

public:

 CTimeCounter();

 bool  IsActive();
 bool  JustFinished(); 
 void  Reset();
 void  Start(double seconds = 0);
 float TimeLeft();


private:

 bool mEnded;
 int  mStart;
 int  mLength;



};


#endif
