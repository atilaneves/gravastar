#ifndef CPILOTINPUTBOT_H
#define CPILOTINPUTBOT_H


#include "CPilotInput.hpp"


class CPilotInputBot: public CPilotInput {

public:

    CPilotInputBot():mLeft(false), mRight(false), mThrust(false), mWeapon(false),
                     mSpecial(false), mSuper(false) { }

    virtual bool Left() const override { return mLeft; }
    virtual bool Right() const override { return mRight; }
    virtual bool Thrust() const override { return mThrust; }
    virtual bool Weapon() const override { return mWeapon; }
    virtual bool Special() const override { return mSpecial; }
    virtual bool Super() const override { return mSuper; }
    virtual bool Start() const override { return false; }
    virtual bool MenuUp() const override { return false; }
    virtual bool MenuDown() const override { return false; }
    virtual bool MenuSelect() const override { return false; }
    virtual bool MenuCancel() const override { return false; }

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
