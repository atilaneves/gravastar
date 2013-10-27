#include "CVersusMenu.hpp"
#include "CCycleLeaf.hpp"
#include "CCycleString.hpp"
#include "CCycleTeam.hpp"
#include "CMenuIconCycle.hpp"
#include "COptionsMenu.hpp"
#include "CShipMenu.hpp"
#include "CMeleeOptions.hpp"
#include "CGravMenu.hpp"

CVersusMenu::CVersusMenu(const CSprite *cursorSprite,
                         const CGravMenu &gravMenu):
    CStringMenu("Versus"),
    mGravMenu(gravMenu),
    mCursor(*this, cursorSprite) {

    AddMenu(mShipMenu    = new CShipMenu(*this));
    CreateTypes();
    AddMenu(mNbHumans    = new CCycleLeaf("Number of Players: ", 4, 0));
    AddMenu(mNbBots      = new CCycleLeaf("Number of Bots: ", 4, 0));
    AddMenu(mLimit       = new CCycleLeaf("Number of Ships: ", 10, 1));
    AddMenu(mPowerupRate = new CCycleLeaf("Powerup Rate: ", 10, 0));
    CreateTeams();

    mNbHumans->SetCycle(1);
    mNbBots->SetCycle(1);
    mLimit->SetCycle(5);
    mPowerupRate->SetCycle(5);
}


void CVersusMenu::CreateTeams() {
    mTeams.resize(kMaxNbPilots);

    for(unsigned int i = 0; i < kMaxNbPilots; i++) {
        char playerName[100];
        sprintf(playerName, "Player%d", i + 1);
        AddMenu(mTeams[i] = new CCycleTeam(playerName));
        mTeams[i]->SetCycle(i);
    }
}


void CVersusMenu::CreateTypes() {
    strings_t strings{ "Survival", "Frag Limit", "Time Limit", "Squad" };
    AddMenu(mMeleeType = new CCycleString("Game Type", strings,
                                          strings.size() - 1, 0));
}


void CVersusMenu::Update(CRootMenu &rootMenu) {
    KeepInBounds();
    SetTypeString();
}


void CVersusMenu::KeepInBounds() {
    if(GetNbPilots() > kMaxNbPilots)
        mNbBots->SetCycle(kMaxNbPilots - mNbHumans->GetCycle());

    if(mNbHumans->GetCycle() == 0 && mNbBots->GetCycle() == 0)
        mNbHumans->SetCycle(1);
}


void CVersusMenu::SetTypeString() {
    if(mMeleeType->GetString() == "Time Limit")
        mLimit->SetIconTitle("Number of Minutes: ");
    else if(mMeleeType->GetString() == "Frag Limit")
        mLimit->SetIconTitle("Number of Frags: ");
    else
        mLimit->SetIconTitle("Number of Ships: ");
}


int CVersusMenu::GetNbPilots() const {
    return mNbHumans->GetCycle() + mNbBots->GetCycle();
}


const CTeam& CVersusMenu::GetPilotTeam(int p) const {
    return mTeams[p]->GetTeam();
}


std::string CVersusMenu::GetPilotName(int p) const {
    return mTeams[p]->GetTitle();
}


std::string CVersusMenu::GetPilotType(int p) const {
    return p < mNbHumans->GetCycle() ? "Human" : "Bot";
}


float CVersusMenu::GetPowerupRate() const {
    return (0.05 * mPowerupRate->GetCycle()) / mPowerupRate->GetMax();
}


CMeleeOptions CVersusMenu::GetMeleeOptions() const {
    return CMeleeOptions(GetMeleeType(), mShipMenu->GetLevelNb(),
                         GetPowerupRate());
}


std::string CVersusMenu::GetMeleeType() const {
    return mMeleeType->GetString();
}


int CVersusMenu::GetNbShips() const {
    return mLimit->GetCycle();
}


int CVersusMenu::GetNbShips(int p) const {
    return (int)GetShipTypes(p).size();
}


std::string CVersusMenu::GetShipType(int p, int s) const {
    return mShipMenu->GetShipType(p, s);
}


const shipTypes_t& CVersusMenu::GetShipTypes(int p) const {
    return mShipMenu->GetShipTypes(p);
}

CGravOptions CVersusMenu::GetGravOptions() const {
    return CGravOptions(GetMeleeOptions(), GetClientOptions());
}

CClientOptions CVersusMenu::GetClientOptions() const {
    return mGravMenu.GetClientOptions(GetNbPilots());
}

std::vector<CPilotOptions> CVersusMenu::GetPilotOptions(int nbPilots,
                                                        const std::vector<CPilotInputOptions>& pilotInputOpts) const {

    std::vector<CPilotOptions> pilotOptions;

    for(int i = 0; i < nbPilots; ++i)
        pilotOptions.emplace_back(GetPilotName(i),
                                  GetPilotType(i),
                                  GetPilotTeam(i),
                                  GetShipTypes(i),
                                  pilotInputOpts[i]);
    return pilotOptions;
}
