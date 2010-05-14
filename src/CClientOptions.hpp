#ifndef CCLIENTOPTIONS_H
#define CCLIENTOPTIONS_H


#include "CPilotOptions.hpp"
#include "CPilotInput.hpp"


typedef std::vector<CPilotOptions> pilotOptions_t;

class CClientOptions {

public:

  CClientOptions();
  CClientOptions(const pilotOptions_t &options, bool ww, int w, int h,
		 int soundVol, int musicVol, bool smart);

                 int   GetHeight() const { return mScreenHeight;  }
                 int   GetMusicVolume() const { return mMusicVolume; }
                 int   GetSoundVolume() const { return mSoundVolume; }
                 int   GetWidth()  const { return mScreenWidth;   }
        unsigned int   GetNbPilots()     const { return mPilots.size(); }
  const CPilotOptions& GetPilotOptions(unsigned int p) const { 
    return mPilots[p]; }
                 bool  IsSmartSplit() const { return mSmartSplit; }
                 bool  IsWindowed() const { return mWindowed; }
                 void  Save() const;
                 void  SetAllBots();


private:

  pilotOptions_t mPilots;
  bool mWindowed;
  int  mScreenWidth;
  int  mScreenHeight;
  int  mSoundVolume;
  int  mMusicVolume;
  bool mSmartSplit;

  void Load();
  void SetDefaults();

};


#endif
