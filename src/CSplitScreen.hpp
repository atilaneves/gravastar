#ifndef CSPLITSCREEN_H
#define CSPLITSCREEN_H

//implements a split screen, shows a window of a larger canvas


#include "CSubCanvas.hpp"
#include "CSubDisplay.hpp"
#include "CScreenPos.hpp"
#include "CVector2.hpp"
#include "CRadar.hpp"
#include <vector>
class CPilot;


class CSplitScreen: public CSubDisplay {

public:

    enum { kSplitBorder=20 };
    using DisplayPilots = CRadar::DisplayPilots;

    CSplitScreen(const CCanvas &levelCanvas, CCanvas &drawCanvas,
                 int width, int height,
                 int drawX, int drawY);
    CSplitScreen(const CSplitScreen &split);

    void       DrawRadar(const DisplayPilots& pilots, const DisplayPilots& humans);
    CScreenPos GetCentre(const DisplayPilots& pilots);
    DisplayPilots   GetHumans(const DisplayPilots& pilots);
    void       Grab(const DisplayPilots& pilots);


private:

    enum { kStatsCanvasWidth = 100, kStatsCanvasHeight = 50 };

    CCanvas        mStatsCanvas;
    CSubCanvas     mSubCanvas;
    const CCanvas* mLevelCanvas;
    CRadar         mRadar;

    CScreenPos GetGrabPos(const DisplayPilots& pilots);
    int        GetRealGrabPos(int pos, int subLength, int levelLength);
    void       DrawStats(const CDisplayPilot& pilot, int x, int y);

};


#endif
