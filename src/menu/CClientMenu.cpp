#include "CClientMenu.hpp"
#include "CGravMenu.hpp"
#include "CGravClient.hpp"
#include "CVersusMenu.hpp"
#include "output.hpp"


CClientMenu::CClientMenu(const CSprite *cursorSprite, CGravMenu& gravMenu):
    CCursorMenu<CStringMenu>(cursorSprite, "Client"),
    mVersusMenu(gravMenu.GetVersusMenu()) {

}


void CClientMenu::Run(CRootMenu &rootMenu) {
    printCentre("Connecting to server...");
    CGravClient gravClient("127.0.0.1", 12346);

    printCentre("Waiting for server...");
    gravClient.Run(rootMenu, mVersusMenu.GetClientOptions());
}
