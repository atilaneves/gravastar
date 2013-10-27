#ifndef CPILOTINPUTPROXY_H_
#define CPILOTINPUTPROXY_H_


#include "CPilotInput.hpp"
class Cereal;


class CPilotInputProxy: public CPilotInput {
public:

    CPilotInputProxy();
    CPilotInputProxy(bool left, bool right, bool thrust,
                     bool weapon, bool special, bool super, bool start);

    void cerealise(Cereal& cereal);

    virtual bool Left()       const override { return mLeft; }
    virtual bool Right()      const override { return mRight; }
    virtual bool Thrust()     const override { return mThrust; }
    virtual bool Weapon()     const override { return mWeapon; }
    virtual bool Special()    const override { return mSpecial; }
    virtual bool Super()      const override { return mSuper; }
    virtual bool Start()      const override { return mStart; }
    virtual bool MenuUp()     const override { return false; }
    virtual bool MenuDown()   const override { return false; }
    virtual bool MenuSelect() const override { return false; }
    virtual bool MenuCancel() const override { return false; }

private:

    bool mLeft, mRight, mThrust, mWeapon, mSpecial, mSuper, mStart;

};



#endif // CPILOTINPUTPROXY_H_
