#ifndef CMELEEONSERVER_H_
#define CMELEEONSERVER_H_


#include "CMelee.hpp"


class CMeleeOnServer: public CMelee {
public:
    using pilots_t = CGravScreen::pilots_t;
    using Pilots = std::vector<CPilot*>;

    CMeleeOnServer(const CGravOptions &options);
    ~CMeleeOnServer();

    virtual void Run() override;

private:

    CPilot*  CreatePilot(const CPilotOptions&, unsigned pilotIndex);
    void     Update(float dt);

protected:

    Pilots mPilots;

    Pilots   GetActivePilots() const;

};


#endif // CMELEEONSERVER_H_
