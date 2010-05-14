#ifndef CSPECIALTIMER_H
#define CSPECIALTIMER_H


#include "CTimer.hpp"


class CSpecialTimer:public CTimer {

public:

  static CSpecialTimer& Instance(int bps = 20)
  { static CSpecialTimer specialTimer(bps);
    return specialTimer; }


private:

  CSpecialTimer(int bps);
  CSpecialTimer(const CSpecialTimer&);

};

#endif
