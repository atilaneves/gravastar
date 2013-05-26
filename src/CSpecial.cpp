#include "CSpecial.hpp"
#include "CShip.hpp"
#include "CShipBluePrint.hpp"
#include "CSpecialTimer.hpp"
#include "CPilot.hpp"
#include "CPilotInput.hpp"
#include "CEMP.hpp"
#include "CEMB.hpp"


CSpecial::CSpecial(const CShipBluePrint &bluePrint, CShip &ship):
    mShip(ship), mTeam(bluePrint.mTeam),
    mRate(bluePrint.mSpecialRate), mMaxGauge(bluePrint.mMaxGauge),
    mGauge(mMaxGauge), mDepletion(bluePrint.mDepletion),
    mRecovery(bluePrint.mRecovery), mUsing(false),
    mRepairSound(bluePrint.mSounds.mRepairSound) {

}


void CSpecial::ApplyInput(const CPilotInput& input) {
    mUsing = input.Special();
}


void CSpecial::Update(float dt) {
    if(mUsing && CanUse() &&
       CSpecialTimer::Instance().IsReady(mShip.GetPilot().GetIndex(), mRate)) {
        LoseGauge(mDepletion * GetDepletionScale(dt)); //spend some
        mShip.UseSpecial(dt);
    }
    else //slowly recover special
        LoseGauge(-mRecovery * dt);

    if(!mUsing || !CanUse())
        NotUsing(); //what happens when the ship stops using its special

    mUsing = false;
}


void CSpecial::LoseGauge(float amount) {
    int oldGauge = int(mGauge);
    mGauge -= amount;
    if(mGauge < 0)             mGauge = 0;
    if(mGauge > mMaxGauge)     mGauge = mMaxGauge;
    if(int(mGauge) > oldGauge) mRepairSound.Play(mShip.GetPos());
}


bool CSpecial::CanUse() const {
    return mGauge >= mDepletion && !mShip.IsEffectOn(CEMP::GetID()) &&
        !mShip.IsEffectOn(CEMB::GetID());
}
