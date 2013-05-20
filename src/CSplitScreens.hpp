#ifndef CSPLITSCREENS_H
#define CSPLITSCREENS_H


#include "CSplitScreen.hpp"
#include <vector>


class CSplitScreens {

public:

    using pilots_t = CSplitScreen::pilots_t;
    virtual ~CSplitScreens() { }

    CScreenPos GetCentre(const pilots_t& pilots) {
        return mSplitScreens[0].GetCentre(pilots); }
    pilots_t   GetHumans(const pilots_t& pilots) {
        return mSplitScreens[0].GetHumans(pilots);
    }

    virtual void DrawRadar(const pilots_t& pilots) = 0;
    virtual void Grab(const pilots_t& pilots) = 0;


protected:

    std::vector<CSplitScreen> mSplitScreens;

    void push_back(const CSplitScreen &splitScreen) {
        mSplitScreens.push_back(splitScreen); }


};


#endif
