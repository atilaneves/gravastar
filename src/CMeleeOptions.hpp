#ifndef CMELEEOPTIONS_H
#define CMELEEOPTIONS_H


#include <string>
#include <utility>

class CMeleeOptions {

public:
  CMeleeOptions(std::string type, int levelNb, float powerupRate)
      : mType(std::move(type)), mLevelNb(levelNb), mPowerupRate(powerupRate) {}

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
