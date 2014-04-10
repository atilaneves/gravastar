#ifndef CPILOTS_H
#define CPILOTS_H


class CPilot;
#include <vector>


class CPilots {

public:

  static void    AddPilot(CPilot* p) { sPilots.push_back(p); }
  static int     GetNbLivePilots();
  static int     GetNbPilots()       { return int(sPilots.size()); }
  static CPilot& GetPilot(int p)     { return *sPilots[p]; }
  static bool    IsAlone(CPilot& pilot);
  static bool    IsCoastClear(CPilot &pilot);
  static void    RemoveAll()         { sPilots.resize(0); }


private:

  static std::vector<CPilot*> sPilots; //ptrs to pilots

};

#endif
