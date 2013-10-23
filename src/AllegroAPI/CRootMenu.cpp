#include "CRootMenu.hpp"
#include "CMenuIconNull.hpp"
#include "CStringMenu.hpp"
#include "CResolution.hpp"
#include "CKeyboard.hpp"
#include "CNullBackground.hpp"
#include "CNullSong.hpp"
#include "CFont.hpp"
#include "CMenuIconString.hpp"
#include "CKeyboard.hpp"


CRootMenu::CRootMenu(bool windowed, int screenWidth, int screenHeight,
                     const CFont &font, CSprite *cursorSprite):
    mCanvas(new CCanvas(screenWidth, screenHeight)),
    mMenu(new CMenuIconNull()), //main menu you see at the start
    mCursor(mMenu, cursorSprite),
    mFont(font),
    mTitle(new CNullBackground),
    mBackground(new CNullBackground),
    mSong(new CNullSong) {

    CResolution::SetWindowed(windowed);
    CResolution::SetMode(screenWidth, screenHeight);
    CStringMenu::SetFont(&mFont);
    CKeyboard::Clear();
    mSong->PlayLoop();

}


void CRootMenu::BeforeMenu() {
    mCanvas->Clear();
    mBackground->Draw(*mCanvas);
    mTitle->Draw(*mCanvas);
    mSong->Poll();
}


void CRootMenu::AfterMenu() {
    mSong->Poll();
    mCanvas->Flip();
}


void CRootMenu::NewCanvas(int w, int h) {
    mCanvas.reset(new CCanvas(w, h));
    mBackground->NewCanvas(w, h);
    BeforeMenu();
    AfterMenu();
}


void CRootMenu::Run() {
    do mMenu.Run(*this);
    while(!Exit());
    AtExit();
}


bool CRootMenu::Exit() {

    while(true) {
        BeforeMenu();
        mMenu.Draw(*mCanvas);
        const int x = mCanvas->GetWidth() / 2;
        const int y = (2*mCanvas->GetHeight()) / 3;
        mFont.PrintCentre(*mCanvas, x, y, CMenuIconString::GetMenuHi(), -1,
                          "Really quit? (Y/N)");
        AfterMenu();
        if(CKeyboard::KeyPressed(CKeyboard::kY)) return true;
        if(CKeyboard::KeyPressed(CKeyboard::kN)) return false;
    }

    return false;
}


void CRootMenu::AddMenu(CMenu *menu) {
    mMenu.AddMenu(menu);
}
