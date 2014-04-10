#ifndef CPILOTINPUTKEY_H
#define CPILOTINPUTKEY_H


#include "CPilotInput.hpp"
class CPilotInputOptions;


class CPilotInputKey: public CPilotInput {

public:

    CPilotInputKey(const CPilotInputOptions& options);

    virtual bool Left() const override;
    virtual bool Right() const override;
    virtual bool Thrust() const override;
    virtual bool Weapon() const override;
    virtual bool Special() const override;
    virtual bool Super() const override;
    virtual bool Start() const override;
    virtual bool MenuUp() const override;
    virtual bool MenuDown() const override;
    virtual bool MenuSelect() const override;
    virtual bool MenuCancel() const override;

private:

    const int mLeft, mRight, mThrust, mWeapon, mSpecial, mSuper, mStart;

};

#endif
