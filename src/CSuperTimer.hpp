#ifndef CSUPERTIMER_H
#define CSUPERTIMER_H


#include "CTimer.hpp"


class CSuperTimer:public CTimer {

public:

  static CSuperTimer& Instance(int bps=60)
  { static CSuperTimer superTimer(bps); return superTimer; }


private:

 CSuperTimer(int bps);
 CSuperTimer(const CSuperTimer&);

};

#endif
