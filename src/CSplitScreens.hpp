#ifndef CSPLITSCREENS_H
#define CSPLITSCREENS_H


#include "CSplitScreen.hpp"
#include <vector>


class CSplitScreens {

public:

    using DisplayPilots = CSplitScreen::DisplayPilots;
    virtual ~CSplitScreens() { }

    CScreenPos GetCentre(const DisplayPilots& pilots) {
        return mSplitScreens[0].GetCentre(pilots); }
    DisplayPilots   GetHumans(const DisplayPilots& pilots) {
        return mSplitScreens[0].GetHumans(pilots);
    }

    virtual void DrawRadar(const DisplayPilots& pilots) = 0;
    virtual void Grab(const DisplayPilots& pilots) = 0;


protected:

    std::vector<CSplitScreen> mSplitScreens;

    void push_back(const CSplitScreen &splitScreen) {
        mSplitScreens.push_back(splitScreen); }


};


#endif
