#ifndef CSTATS_H
#define CSTATS_H


#include "CMelee.hpp"


class CStats {

public:

  static void AddFrag(int pilotIndex)    { mFrags[pilotIndex]++; }
  static int  GetNbFrags(int pilotIndex) { return mFrags[pilotIndex]; }
  static void AddWin(int pilotIndex)     { mWins[pilotIndex]++; }
  static int  GetNbWins(int pilotIndex)  { return mWins[pilotIndex]; }


private:

  static int mFrags[CMelee::kMaxNbPilots];
  static int mWins[CMelee::kMaxNbPilots];

};



#endif
