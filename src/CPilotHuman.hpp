#ifndef CPILOTHUMAN_H
#define CPILOTHUMAN_H


#include "CPilot.hpp"


class CPilotHuman: public CPilot {

public:

  CPilotHuman(const CPilotOptions &options, const CShipYard &shipYard,
              CMeleeScore& meleeScore);

private:

  bool mReleasedStart;

  virtual void CheckControls(CClientSocket* clientSocket);


};


#endif
