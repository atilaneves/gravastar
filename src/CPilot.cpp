#include "CPilot.hpp"
#include "CPilotOptions.hpp"
#include "CPilotInputFactory.hpp"
#include "CShipYard.hpp"
#include "CShips.hpp"
#include "CPilots.hpp"
#include "CMeleeScore.hpp"
#include "CStats.hpp"


int CPilot::sIndex = 0;

CPilot::CPilot(bool hasSplitScreen,
               const CPilotOptions &options, const CShipYard &shipYard,
               CMeleeScore &meleeScore):
    mHasSplitScreen(hasSplitScreen),
    mIndex(sIndex++),
    mNbShips(options.GetNbShips() + 1), //gets dec'ed by 1 w NextShip
    mNbFrags(0), mSuperGauge(0),
    mShip(0), mStats(*this),
    mInput(CPilotInputFactory::CreateInput(options.GetInputOptions())),
    mOptions(options), mShipYard(shipYard), mMeleeScore(meleeScore) {

    NextShip();
    CPilots::AddPilot(this);
}


bool CPilot::IsSurvival() const {
    return mMeleeScore.GetMeleeType() == "Survival" ||
        mMeleeScore.GetMeleeType() == "Squad";
}


void CPilot::NextShip() {
    if(IsSurvival() || mNbShips > (int)mOptions.GetNbShips()) mNbShips--;
    if(mNbShips <= 0) return; //no more ships!
    const std::string& name = GetShipName(GetShipIndex());
    const CTeam& team = mOptions.GetTeam();
    if(mShip) mSuperGauge = mShip->GetWeapons().GetSuperGauge();
    mShip = mShipYard.CreateShip(name, team, *this);
    mStats.SetStatSprite(&(GetShipStatSprite(GetShipIndex())));
    mShip->GetWeapons().SetSuperGauge(mSuperGauge);
    mShip->Draw();
}


int CPilot::GetScore() const {
    return IsSurvival() ? mNbShips : mNbFrags;
}


void CPilot::AddDamage(float amount, CPilot &pilot) {
    //ad-hoc solution to plasma - place a dmg limit of 10
    if(!IsAlive()) return;
    if(amount <= 10.1 && !GetShip().GetWeapons().IsSuperActive() &&
       &pilot != this)
        GetShip().GetWeapons().AddSuperGauge(amount);
    if(amount < 0) //powerup
        GetShip().GetWeapons().AddSuperGauge(1000); //fill it up!
}


void CPilot::AddFrag(CPilot &pilot) {
    if(&pilot != this) mNbFrags++;
    CStats::AddFrag(GetIndex());
}


const std::string& CPilot::GetName() const {
    return mOptions.GetName();
}


bool CPilot::IsAlive() const {
    return mNbShips > 0 && mShip;
}


const CShipStatSprite& CPilot::GetShipStatSprite(int index) const {
    const std::string& name = GetShipName();
    const CTeam& team = mOptions.GetTeam();
    return *mShipYard.GetBluePrint(name, team).GetStatSprite();
}


CDisplayPilot CPilot::MakeDisplayPilot() {
    return { static_cast<uint8_t>(mIndex),
            GetShip().GetPos(), GetShip().GetVel(),
            mOptions.GetTeam(), static_cast<uint8_t>(GetScore()),
            mStats,
            GetShip().IsAlive(), HasSplitScreen()};
}
