#include "CMeleeDemo.hpp"
#include "CGravOptions.hpp"
#include "CKeyboard.hpp"
#include "CJoystick.hpp"
#include "CDirectory.hpp"
#include "CDataFile.hpp"
#include "CLevelCounter.hpp"
#include "CMeleeFactory.hpp"
#include <stdio.h>
#include <stdlib.h>


REG_MELEE("Demo", CMeleeDemo)


CMeleeDemo::CMeleeDemo(const CGravOptions &options):
    CMeleeOnServer(RandomOptions(options.GetClientOptions())) {

    mEndCounter.Start(45); //this many seconds of demo
    CKeyboard::Clear();
    //CScreenSorter::SetPrintPressKey(true);
}


CMeleeDemo::~CMeleeDemo() {
    //CScreenSorter::SetPrintPressKey(false);
}


bool CMeleeDemo::IsGameOver() {
    if(CKeyboard::KeyPressedAny() || CJoystick::IsPressedAny()) {
        mEndCounter.Reset();
        mEndCounter.Start(0.001); //end pretty much now
    }
    return true;
}


int CMeleeDemo::GetWinner() {
    return -1;
}


CGravOptions CMeleeDemo::RandomOptions(CClientOptions clientOptions) const {
    float powerupRate = 0.1;
    CLevelCounter levelCounter;
    CMeleeOptions meleeOptions("Demo", levelCounter.GetRandomLevel(),
                               powerupRate);
    clientOptions.SetAllBots();
    return CGravOptions(meleeOptions, clientOptions);
}
