#include "CPhantom.hpp"
#include "CShipFactory.hpp"
#include "CProjLauncher.hpp"
#include "CNose.hpp"
#include "CLevel.hpp"
#include "CAbsorber.hpp"
#include "CWeaponFollow.hpp"
#include "CPilotInput.hpp"
#include "CCoolant.hpp"
#include "CShipBluePrint.hpp"
#include "CShipSounds.hpp"
#include "CEMP.hpp"
#include "CEMB.hpp"
#include <algorithm>
#include <math.h>



static std::string gFollowName = "miniBullet";
static std::string gShotName = "shot";
REG_FOLLOW_SHIP("Phantom", CPhantom, gShotName, gFollowName,
                CFollower, CFollowSpecial)


CPhantom::CPhantom(const CShipBluePrint& bluePrint,
                   CPilot& pilot, CLevel &level):
CShip(bluePrint, pilot, level),
mPhased(false), mHisteresis(false),
mFlashForward(bluePrint.mSounds.mFlashForward) {


}


void CPhantom::ApplyInput(const CPilotInput &controls) {
    CShip::ApplyInput(controls);
    bool phased = mPhased;
    mPhased = controls.Special() && CanPhase();
    if(!phased && mPhased) {
        mFlashForward.Play(mPos);
        mPhaseCounter.Start(0.75);
    }
}


void CPhantom::Update(float dt) {
    const float scale = 20;
    if(mPhased) mWeapons.LoseGauge(scale * mWeapons.GetDepletion() * dt);
    if(!CanPhase()) mPhased = false;
    if(!mPhased) CShip::Update(dt);
    else         mWeapons.Update(0.5 * dt); //so cannon cools down
}


bool CPhantom::CanPhase() {
    if((!mPhased && mPhaseCounter.IsActive()) ||
       IsEffectOn(CEMP::GetID()) || IsEffectOn(CEMB::GetID()))
        return false;
    const float kSmall = 0.75;
    const float kReallySmall = 0.01;
    mHisteresis = mHisteresis ? mWeapons.GetSpecialGauge() < kSmall :
        mWeapons.GetSpecialGauge() < kReallySmall;
    float minGauge = mHisteresis ? kSmall : 0;
    return mWeapons.GetSpecialGauge() > minGauge;
}


void CPhantom::UseWeapon(float dt) {
    float da = M_PI / 15; //small variation in angle
    SpawnShot(dt, -da);
    SpawnShot(dt, da);
    SpawnShot(dt, -2*da);
    SpawnShot(dt, 2*da);
}


void CPhantom::SpawnShot(float dt, float dAngle) {
    const double dist = 0.65, velNorm = 400;
    CVector2 vel = CProjLauncher::GetLaunchVel(*this, velNorm) + mVel;
    CVector2 pos = CProjLauncher::GetLaunchPos(mWeapons.GetSpecialSprite(), dt,
                                               *this, dist, dAngle);
    mWeapons.UseWeaponAt(pos, vel, gShotName);
}


void CPhantom::UseSpecial(float dt) {

}


void CPhantom::UseSuper(float dt, bool use) {
    float duration = 5;
    StartEffect(CCoolant::GetID(), duration);
}


CLevelSprite CPhantom::Draw() {
    return mPhased ? CLevelSprite{} : CShip::Draw();
}
