#include "output.hpp"
#include "CFont.hpp"
#include "fontsdat.h"
#include "CCanvas.hpp"


void printCentre(const std::string& str) {
    static CFont font{MetroStyleExtendedBoldItalic28};
    CCanvas screenCanvas(screen);
    screenCanvas.Clear();
    font.PrintCentre(screenCanvas, screenCanvas.GetWidth()/2,
                      screenCanvas.GetHeight()/2, makecol(255, 255, 255), -1,
                      str);
}
