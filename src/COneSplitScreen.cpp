#include "COneSplitScreen.hpp"
#include "CCanvas.hpp"


COneSplitScreen::COneSplitScreen(const CCanvas &levelCanvas,
                                 CCanvas &drawCanvas) {

    push_back(CSplitScreen(levelCanvas, drawCanvas,
                           drawCanvas.GetWidth(), drawCanvas.GetHeight(),
                           0,0));
}


void COneSplitScreen::Grab(const DisplayPilots& pilots) {
    mSplitScreens[0].Grab(pilots);
}


void COneSplitScreen::DrawRadar(const DisplayPilots& pilots) {
    mSplitScreens[0].DrawRadar(pilots, GetHumans(pilots));
}
