#ifndef CMELEEOPTIONS_H
#define CMELEEOPTIONS_H


#include <string>


class CMeleeOptions {

public:

  CMeleeOptions(const std::string &type, int levelNb, float powerupRate):
    mType(type), mLevelNb(levelNb), mPowerupRate(powerupRate) { }

  CMeleeOptions():mType("Survival"), mLevelNb(4), mPowerupRate(0.1) { }

  int   GetLevelNb()     const { return mLevelNb; }
  float GetPowerupRate() const { return mPowerupRate; }
  const std::string& GetType() const { return mType; }


private:

  std::string mType;
  int   mLevelNb;
  float mPowerupRate;

};


#endif
