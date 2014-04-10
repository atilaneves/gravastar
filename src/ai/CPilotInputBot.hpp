#ifndef CPILOTINPUTBOT_H
#define CPILOTINPUTBOT_H


#include "CPilotInput.hpp"


class CPilotInputBot: public CPilotInput {

public:

    CPilotInputBot():mLeft(false), mRight(false), mThrust(false), mWeapon(false),
                     mSpecial(false), mSuper(false) { }

    virtual bool Left()       const { return mLeft;    }
    virtual bool Right()      const { return mRight;   }
    virtual bool Thrust()     const { return mThrust;  }
    virtual bool Weapon()     const { return mWeapon;  }
    virtual bool Special()    const { return mSpecial; }
    virtual bool Super()      const { return mSuper;   }
    virtual bool Start()      const { return false;    }
    virtual bool MenuUp()     const { return false;    }
    virtual bool MenuDown()   const { return false;    }
    virtual bool MenuSelect() const { return false;    }
    virtual bool MenuCancel() const { return false;    }

    void SetLeft(bool s = true)    { mLeft    = s; }
    void SetRight(bool s = true)   { mRight   = s; }
    void SetThrust(bool s = true)  { mThrust  = s; }
    void SetWeapon(bool s = true)  { mWeapon  = s; }
    void SetSpecial(bool s = true) { mSpecial = s; }
    void SetSuper(bool s = true)   { mSuper   = s; }


private:

    bool mLeft, mRight, mThrust, mWeapon, mSpecial, mSuper;

};


#endif
