#include "CRedefineIcon.hpp"
#include "CRedefineMenu.hpp"
#include "CMenuIconString.hpp"
#include "CColour.hpp"
#include "CRectFill.hpp"
#include "CStringMenu.hpp"
#include "CVersusMenu.hpp"
#include "CCycleString.hpp" //strings_t
#include "CDefineButtonMenu.hpp"
#include "CPilotInput.hpp"
#include "fontsdat.h"


CRedefineIcon::CRedefineIcon(CRedefineMenu &redefine,
                             const CVersusMenu &versus,
                             int pilotNb):
    mRedefine(redefine), mVersus(versus), mPilotNb(pilotNb),
    mFont(CStringMenu::GetFont()), mPilotFont(EmpireBuilderDocument9) {

}


void CRedefineIcon::Draw(CCanvas &canvas, int x, int y, bool highlight) const {
    y += 15; //offset it a bit
    DrawRectangles(canvas, x, y);
    mPilotFont.Print(canvas, x + 8, y - 65, CColour::GetBlack(), -1,
                     mVersus.GetPilotName(mPilotNb));
    DrawButtons(canvas, x, y, highlight);
}


void CRedefineIcon::DrawRectangles(CCanvas &canvas, int x, int y) const {
    int blockCol = mVersus.GetPilotTeam(mPilotNb).GetDarkColour();
    int xl1 = x-15, xl2 = x-5, xr1 = x+80, xr2 = x+90;
    CRectFill r1(canvas, xl1, y-50,  xl2, y+kWidth, blockCol); //vertical left
    CRectFill r2(canvas, xr1, y-50,  xr2, y+kWidth, blockCol); //vertivcal right
    CRectFill r3(canvas, xl1, y-15,  xr2, y-5,      blockCol);   //horizontal top
    CRectFill r4(canvas, xl1, y+110, xr2, y+kWidth, blockCol); //horizontal bottom
    CRectFill r5(canvas, xl1, y-80,  xr2, y-35,     blockCol);  //top bit
}


void CRedefineIcon::DrawButtons(CCanvas &canvas, int x, int y,
                                bool highlight) const {
    int dy = (3*mFont.GetHeight()) / 2;
    for(int i = 0; i < CPilotInput::GetNbControls(); i++) {
        mFont.Print(canvas, x, y + i*dy, CMenuIconString::GetColour(highlight), -1,
                    CPilotInput::GetName(i) + ": " +
                    mRedefine.GetButton(CPilotInput::GetName(i)).GetButtonName());
    }

}


int CRedefineIcon::GetHeight() const {
    return mFont.GetHeight();
}


int CRedefineIcon::GetWidth() const {
    return kWidth;
}
