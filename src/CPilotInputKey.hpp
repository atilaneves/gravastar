#ifndef CPILOTINPUTKEY_H
#define CPILOTINPUTKEY_H


#include "CPilotInput.hpp"
class CPilotInputOptions;


class CPilotInputKey: public CPilotInput {

public:

  CPilotInputKey(const CPilotInputOptions& options);

  virtual bool Left()    const;
  virtual bool Right()   const;
  virtual bool Thrust()  const;
  virtual bool Weapon()  const;
  virtual bool Special() const;
  virtual bool Super()   const;
  virtual bool Start()   const;


private:

  const int mLeft, mRight, mThrust, mWeapon, mSpecial, mSuper, mStart;

};

#endif
