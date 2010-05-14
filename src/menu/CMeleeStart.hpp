#ifndef CMELEESTART_H
#define CMELEESTART_H


#include "CCycleString.hpp"
#include "CPilotOptions.hpp"
#include <vector>
class CGravMenu;


class CMeleeStart: public CCycleString {

public:

  CMeleeStart(const CGravMenu &gravMenu, const strings_t& levelNames);
  virtual void Run(CRootMenu &rootMenu);

  int GetNbLevels() const { return mCycle.GetMax(); }


private:

  const CGravMenu &mGravMenu;


};


#endif
