#include "CTwoSplitScreens.hpp"
#include "CCanvas.hpp"
#include <assert.h>


CTwoSplitScreens::CTwoSplitScreens(const CCanvas &levelCanvas,
                                   CCanvas &drawCanvas) {

    push_back(CSplitScreen(levelCanvas, drawCanvas,
                           drawCanvas.GetWidth(), drawCanvas.GetHeight() / 2,
                           0, 0));

    push_back(CSplitScreen(levelCanvas, drawCanvas,
                           drawCanvas.GetWidth(), drawCanvas.GetHeight() / 2,
                           0, drawCanvas.GetHeight() / 2));
}


void CTwoSplitScreens::Grab(const pilots_t& pilots) {
    assert(pilots.size() == 2);
    for(unsigned int i = 0; i < pilots.size(); ++i) {
        pilots_t pilot{ pilots[i] };
        mSplitScreens[i].Grab(pilot);
    }
}


void CTwoSplitScreens::DrawRadar(const pilots_t& pilots) {
    pilots_t humans = GetHumans(pilots);
    for(unsigned int i = 0; i < humans.size(); ++i) {
        pilots_t pilot(1, humans[i]);
        mSplitScreens[i].DrawRadar(pilots, pilot);
    }
}
