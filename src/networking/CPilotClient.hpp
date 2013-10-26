#ifndef CPILOTCLIENT_H_
#define CPILOTCLIENT_H_

#include "CPilot.hpp"

class CPilotClient: public CPilot {
public:
    CPilotClient(const CPilotOptions &options, const CShipYard &shipYard,
                 CMeleeScore& meleeScore);
private:

    virtual void CheckControls(CClientSocket* clientSocket) override;
};


#endif // CPILOTCLIENT_H_
