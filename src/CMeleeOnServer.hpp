#ifndef CMELEEONSERVER_H_
#define CMELEEONSERVER_H_


#include "CMelee.hpp"


class CMeleeOnServer: public CMelee {
public:

    CMeleeOnServer(const CGravOptions &options);

    virtual void Run() override;

private:

    void Update(float dt);

protected:

    Pilots GetActivePilots() const;

};


#endif // CMELEEONSERVER_H_
