#include "CClientOptions.hpp"
#include "CDataFile.hpp"
#include <allegro.h>


CClientOptions::CClientOptions(const AllPilotOptions& options,
                               bool ww, int w, int h, int soundVol,
                               int musicVol, bool smart):
    mPilots(options), mWindowed(ww), mScreenWidth(w), mScreenHeight(h),
    mSoundVolume(soundVol), mMusicVolume(musicVol),
    mSmartSplit(smart) {

}

CClientOptions::CClientOptions(const AllPilotOptions& options,
                               const CClientOptions& other):
    CClientOptions(options, other.mWindowed,
                   other.mScreenWidth, other.mScreenHeight,
                   other.mSoundVolume, other.mMusicVolume,
                   other.mSmartSplit) {

    //take input from passed-in options
    for(unsigned i = 0; i < options.size(); ++i) {
        mPilots[i].SetInputOptions(other.mPilots[i].GetInputOptions());
    }
}


CClientOptions::CClientOptions() {
    SetDefaults();
    Load();
}


CPilotInputOptions gInputOptions[] = {
    CPilotInputOptions("Keyboard", KEY_A, KEY_S, KEY_E, KEY_R, KEY_T,
                       KEY_D, KEY_D, 0),
    CPilotInputOptions("Keyboard", KEY_J, KEY_K, KEY_I, KEY_O, KEY_P,
                       KEY_L, KEY_L, 1),
    CPilotInputOptions("Keyboard", KEY_1, KEY_2, KEY_3, KEY_4, KEY_5,
                       KEY_N, KEY_N, 2),
    CPilotInputOptions("Keyboard", KEY_6, KEY_7, KEY_8, KEY_9, KEY_0,
                       KEY_M, KEY_M, 3)};

static const int kMaxNbPilots = 4;

std::string getName(int index) {
    char str[200];
    sprintf(str, "Player%d", index % kMaxNbPilots);
    return str;
}


const CTeam& getTeam(int index) {
    if(index % kMaxNbPilots == 0)      return CTeam::sBlue;
    else if(index % kMaxNbPilots == 1) return CTeam::sRed;
    else if(index % kMaxNbPilots == 2) return CTeam::sGreen;
    else                               return CTeam::sYellow;
}


std::string getType(int index) {
    return index % kMaxNbPilots == 0 ? "Human" : "Bot";
}

static const int kNbButtons = 7;
static const shipTypes_t gShips;

void CClientOptions::SetDefaults() {
    int width, height;
    get_desktop_resolution(&width, &height);
    mWindowed     = false;
    mScreenWidth  = width;
    mScreenHeight = height;
    mMusicVolume  = 10;
    mSoundVolume  = 10;
    mSmartSplit   = true;
    for(int i = 0; i < 4; i++) {
        mPilots.push_back(CPilotOptions(getName(i), getType(i), getTeam(i), gShips,
                                        gInputOptions[i]));
    }
}


static std::string getFileName() {
    return CDataFile::GetFileName("cfg/grav.cfg");
}

void CClientOptions::Load() {
    FILE *fp = fopen(getFileName().c_str(), "r");
    if (fp == nullptr)
      return;
    mPilots.clear();
    fscanf(fp, "%d %d %d", &mScreenWidth, &mScreenHeight, (int*)&mWindowed);
    fscanf(fp, "%d %d %d", &mSoundVolume, &mMusicVolume, (int*)&mSmartSplit);
    for(int i = 0; i < kMaxNbPilots; i++) {
        char controlType[100];
        fscanf(fp, "%s", controlType);
        int bts[kNbButtons];
        for (auto &bt : bts)
          fscanf(fp, "%d", &bt);
        int index = 0;
        mPilots.push_back(CPilotOptions(getName(i), getType(i), getTeam(i), gShips,
                                        CPilotInputOptions(controlType, bts[0],
                                                           bts[1], bts[2], bts[3],
                                                           bts[4], bts[5], bts[6],
                                                           index++)));
    }

    fclose(fp);
}


void CClientOptions::Save() const {
    FILE *fp=fopen(getFileName().c_str(), "w");
    if (fp != nullptr) {
        int windowed = mWindowed ? 0 : 1;
        fprintf(fp,"%d %d %d\n", mScreenWidth, mScreenHeight, windowed);
        fprintf(fp,"%d %d %d\n", mSoundVolume, mMusicVolume, mSmartSplit);
        for( int i=0; i < kMaxNbPilots; i++) {
            fprintf(fp,"%s    ", mPilots[i].GetInputOptions().Type().c_str());
            std::string names[] = {"Left", "Right", "Thrust", "Weapon", "Special",
                                   "Super", "Start"};
            for (auto &name : names)
              fprintf(fp, "%d  ",
                      mPilots[i].GetInputOptions().GetControl(name));
            fprintf(fp,"\n"); //player separator
        }
        fclose(fp);
    }
    else
        fprintf(stderr,"\n*** Error: Could not open %s to write ***\n\n",
                getFileName().c_str());
}


void CClientOptions::SetAllBots() {
  for (auto &elem : mPilots)
    elem.SetBot();
}
