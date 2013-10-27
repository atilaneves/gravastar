#ifndef CMELEEONSERVER_H_
#define CMELEEONSERVER_H_


#include "CMelee.hpp"
class CPilotInputProxy;


class CMeleeOnServer: public CMelee {
public:

    using DisplayPilots = CGravScreen::DisplayPilots;

    CMeleeOnServer(const CGravOptions &options);

    virtual void Run() override;
    void SetControls(int pilotIndex, const CPilotInputProxy& input);

private:

    void Update(float dt);

protected:

    Pilots GetActivePilots() const;

};


#endif // CMELEEONSERVER_H_
