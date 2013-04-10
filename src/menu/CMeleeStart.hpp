#ifndef CMELEESTART_H
#define CMELEESTART_H


#include "CCycleString.hpp"
#include "CPilotOptions.hpp"
#include <vector>
class CVersusMenu;


class CMeleeStart: public CCycleString {

public:

  CMeleeStart(const CVersusMenu &versusMenu, const strings_t& levelNames);
  virtual void Run(CRootMenu &rootMenu);

  int GetNbLevels() const { return mCycle.GetMax(); }


private:

  const CVersusMenu &mVersusMenu;


};


#endif
