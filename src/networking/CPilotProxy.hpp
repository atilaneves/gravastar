#ifndef CPILOTPROXY_H_
#define CPILOTPROXY_H_

#include "CPilot.hpp"

class CPilotProxy: public CPilot {
public:
    CPilotProxy(const CPilotOptions &options, const CShipYard &shipYard,
                 CMeleeScore& meleeScore);
private:

    virtual void CheckControls(CClientSocket* clientSocket) override;
};


#endif // CPILOTPROXY_H_
