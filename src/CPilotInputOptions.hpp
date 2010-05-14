#ifndef CPILOTINPUTOPTIONS_H
#define CPILOTINPUTOPTIONS_H


#include <string>
class CRedefineMenu;
class CCycleStringEnter;


class CPilotInputOptions {

public:

  CPilotInputOptions(const std::string& type, int left, int right, int thrust,
		     int weapon, int special, int super, int start,
		     int index):
    mType(type), mLeft(left), mRight(right), mThrust(thrust), mWeapon(weapon),
    mSpecial(special), mSuper(super), mStart(start), mIndex(index) { }
  CPilotInputOptions(CCycleStringEnter &typeMenu, CRedefineMenu &menu,
		     int index);

  const std::string& Type()    const { return mType;   }
  int          	     Left()    const { return mLeft;   }
  int          	     Right()   const { return mRight;  }
  int          	     Thrust()  const { return mThrust; }
  int          	     Weapon()  const { return mWeapon; }
  int          	     Special() const { return mSpecial; }
  int          	     Super()   const { return mSuper; }
  int          	     Start()   const { return mStart; }
  int 		     GetControl(const std::string& which) const;
  int                GetIndex() const { return mIndex; }


private:

  std::string mType;
  int mLeft, mRight, mThrust, mWeapon, mSpecial, mSuper, mStart, mIndex;

};


#endif
