#ifndef CPILOTSERVER_H_
#define CPILOTSERVER_H_

#include "CPilot.hpp"

class CPilotServer: public CPilot {
public:
    CPilotServer(const CPilotOptions &options, const CShipYard &shipYard,
                 CMeleeScore& meleeScore);
private:

    virtual void CheckControls() override;
};


#endif // CPILOTSERVER_H_
