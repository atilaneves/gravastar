#ifndef CCLIENTOPTIONS_H
#define CCLIENTOPTIONS_H


#include "CPilotOptions.hpp"
#include "CPilotInput.hpp"
#include <vector>


class CClientOptions {
public:

    using AllPilotOptions = std::vector<CPilotOptions>;

    CClientOptions();
    CClientOptions(const AllPilotOptions& options, bool ww, int w, int h,
                   int soundVol, int musicVol, bool smart);
    CClientOptions(const AllPilotOptions& allPilotOptions,
                   const CClientOptions& other);

                    int    GetHeight() const { return mScreenHeight;  }
                    int    GetMusicVolume() const { return mMusicVolume; }
                    int    GetSoundVolume() const { return mSoundVolume; }
                    int    GetWidth()  const { return mScreenWidth;   }
               unsigned    GetNbPilots()     const { return mPilots.size(); }
    const AllPilotOptions& GetAllPilotOptions() const { return mPilots; }
    const CPilotOptions&   GetPilotOptions(unsigned int p) const { 
                               return mPilots[p]; }
                     bool  IsSmartSplit() const { return mSmartSplit; }
                     bool  IsWindowed() const { return mWindowed; }
                     void  Save() const;
                     void  SetAllBots();

private:

    AllPilotOptions mPilots;
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
