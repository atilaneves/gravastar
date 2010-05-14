#ifndef CCLOCK_H
#define CCLOCK_H


#include <time.h>


class CClock {

public:

  static float DeltaS();  //dt in s
  static int   DeltaMS(); //dt in ms
  static void  Reset();   //start again


private:

  static clock_t sClock;

};


#endif
