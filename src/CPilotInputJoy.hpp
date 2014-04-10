#ifndef CPILOTINPUTJOY_H
#define CPILOTINPUTJOY_H


#include "CPilotInput.hpp"
class CPilotInputOptions;


class CPilotInputJoy: public CPilotInput {

public:

  CPilotInputJoy(const CPilotInputOptions& options);

  virtual bool Left()       const;
  virtual bool Right()      const;
  virtual bool Thrust()     const;
  virtual bool Weapon()     const;
  virtual bool Special()    const;
  virtual bool Super()      const;
  virtual bool Start()      const;
  virtual bool MenuUp()     const;
  virtual bool MenuDown()   const;
  virtual bool MenuSelect() const;
  virtual bool MenuCancel() const;


private:

  const int mLeft, mRight, mThrust, mWeapon, mSpecial, mSuper, mStart;
  const int mIndex;

};

#endif
