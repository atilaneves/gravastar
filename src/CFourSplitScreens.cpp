#include "CFourSplitScreens.hpp"
#include "CCanvas.hpp"
#include <assert.h>


CFourSplitScreens::CFourSplitScreens(const CCanvas &levelCanvas,
                                     CCanvas &drawCanvas) {

    push_back(CSplitScreen(levelCanvas, drawCanvas,
                           drawCanvas.GetWidth() / 2,
                           drawCanvas.GetHeight() / 2,
                           0, 0));

    push_back(CSplitScreen(levelCanvas, drawCanvas,
                           drawCanvas.GetWidth() / 2,
                           drawCanvas.GetHeight() / 2,
                           drawCanvas.GetWidth() / 2, 0));

    push_back(CSplitScreen(levelCanvas, drawCanvas,
                           drawCanvas.GetWidth() / 2,
                           drawCanvas.GetHeight() / 2,
                           0, drawCanvas.GetHeight() / 2));

    push_back(CSplitScreen(levelCanvas, drawCanvas,
                           drawCanvas.GetWidth() / 2,
                           drawCanvas.GetHeight() / 2,
                           drawCanvas.GetWidth() / 2,
                           drawCanvas.GetHeight() / 2));
}


void CFourSplitScreens::Grab(const DisplayPilots& pilots) {
    assert(pilots.size() >= 3);
    for(unsigned int i = 0; i < pilots.size(); ++i) {
        DisplayPilots pilot{pilots[i]};
        mSplitScreens[i].Grab(pilot);
    }
}


void CFourSplitScreens::DrawRadar(const DisplayPilots& pilots) {
    DisplayPilots humans = GetHumans(pilots);
    for(unsigned int i = 0; i < humans.size(); ++i) {
        DisplayPilots pilot(1, humans[i]);
        mSplitScreens[i].DrawRadar(pilots, pilot);
    }
}
