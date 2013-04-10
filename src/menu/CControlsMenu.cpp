#include "CControlsMenu.hpp"
#include "CResolution.hpp"
#include "CControlTypeMenu.hpp"
#include "CRedefineMenu.hpp"
#include "CPilotInputOptions.hpp"
#include "CClientOptions.hpp"
#include "CResolution.hpp"
#include "CMenuIconString.hpp"
#include "CFont.hpp"


CControlsMenu::CControlsMenu(const CVersusMenu &versus,
                             const CClientOptions &options):
    CStringMenu("Controls"),
    mCursor(*this),
    mVersus(versus) {

    strings_t titles{ "Keyboard", "Joystick" };
    for(int i = 0; i < kMaxNbPilots; i++) {
        const auto &op = options.GetPilotOptions(i).GetInputOptions();
        mRedefines.push_back(new CRedefineMenu(versus, i, *this, op));
        mControlTypes.push_back(new CControlTypeMenu(*mRedefines[i], op, "",
                                                     titles, 1, 0));
        AddMenu(mControlTypes[i], i);
        AddMenu(mRedefines[i], i);
    }
}

  

int CControlsMenu::GetSubMenuX(int column) const {
    return CMenu::GetSubMenuX(column) + CResolution::GetWidth() / 35;
}


std::vector<CPilotInputOptions> CControlsMenu::GetPilotInputOptions(int nbPilots) const{
    std::vector<CPilotInputOptions> pilotInputOpts;
    for(int i = 0; i < nbPilots; ++i) {
        pilotInputOpts.emplace_back(*mControlTypes[i], *mRedefines[i],
                                    GetJoyIndex(i));
    }

    return pilotInputOpts;
}


int CControlsMenu::GetJoyIndex(int i) const {
    int joyIndex = -1;
    for(int j = 0; j <= i; j++)
        if(mControlTypes[j]->GetString() == "Joystick")
            joyIndex++;
    return joyIndex;
}


void CControlsMenu::Draw(CCanvas &canvas) {
    CMenu::Draw(canvas);
    std::string str1 = "If the start and super buttons are the same ";
    str1 += "the super is ";
    std::string str2 = "performed by pressing weapon and ";
    str2 += "special at the same time";
    CStringMenu::GetFont().Print(canvas, CResolution::GetWidth() / 8,
                                 (CResolution::GetHeight()*17)/20,
                                 CMenuIconString::GetMenuHi(), -1, str1);
  
    CStringMenu::GetFont().Print(canvas, CResolution::GetWidth() / 8,
                                 (CResolution::GetHeight()*17)/20 + 15,
                                 CMenuIconString::GetMenuHi(), -1, str2);
}
