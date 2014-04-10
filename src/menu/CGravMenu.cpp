#include "CGravMenu.hpp"
#include "CDataFile.hpp"
#include "CStarField.hpp"
#include "CTeam.hpp"
#include "CFont.hpp"
#include "CFontTitle.hpp"
#include "CSoundMP3.hpp"
#include "CVersusMenu.hpp"
#include "COptionsMenu.hpp"
#include "CGravOptions.hpp"
#include "CControlsMenu.hpp"
#include "CResolution.hpp"
#include "CColour.hpp"
#include "COnlineMenu.hpp"
#include "deltadat.h"
#include "fontsdat.h"


static CSprite *cursorSprite;


CGravMenu::CGravMenu(const CGravOptions &options):
    CRootMenu(options.GetClientOptions().IsWindowed(),
              options.GetClientOptions().GetWidth(),
              options.GetClientOptions().GetHeight(),
              CFont(0),
              cursorSprite = new CSprite(CDataFile("Ships/Delta.dat").GetData(BLUE_000))),
    mCursorSprite(cursorSprite), mTitle("title"),
    mAdFont(EmpireBuilderDocument9) {

    AddMenu(mVersusMenu = new CVersusMenu(cursorSprite, *this));
    AddMenu(new COnlineMenu(cursorSprite, *this));
    AddMenu(mOptionsMenu = new COptionsMenu(cursorSprite, *mVersusMenu,
                                            CClientOptions()));
    AdoptTitle(new CFontTitle(kFontSpaceAge52,
                              makecol(0, 0, 190), "Gravastar"));
    AdoptBackground(new CStarField(options.GetClientOptions().GetWidth(),
                                   options.GetClientOptions().GetHeight()));
    AdoptSong(new CSoundMP3("../Gravastar"));
    CTeam::LoadColours();
    mTitle.PlayCentre();
}


CClientOptions CGravMenu::GetClientOptions(int nbPilots) const {
    return mOptionsMenu->GetClientOptions(nbPilots);
}


void CGravMenu::AtExit() {
    mOptionsMenu->Save();
}


void CGravMenu::BeforeMenu() {
    CRootMenu::BeforeMenu();
    int x  = CResolution::GetWidth()  - 240;
    int y1 = CResolution::GetHeight() - 113;
    int y2 = CResolution::GetHeight() - 100;
    mAdFont.Print(*mCanvas, x, y1, CColour::GetWhite(), -1,
                  "http://soundclick.com/atilaneves");
    mAdFont.Print(*mCanvas, x, y2, CColour::GetWhite(), -1,
                  "http://myspace.com/dratila");
}
