#ifndef CPILOTHUMAN_H
#define CPILOTHUMAN_H


#include "CPilot.hpp"


class CPilotHuman: public CPilot {

public:

  CPilotHuman(const CPilotOptions &options, const CShipYard &shipYard,
              CMeleeScore& meleeScore);
  virtual ~CPilotHuman() { }

  virtual bool HasSplitScreen() const { return true; }


private:

  bool mReleasedStart;

  virtual void CheckControls();


};


#endif
