#include "CFollowSpecial.hpp"
#include "CShipBluePrint.hpp"
#include "CShip.hpp"
#include "CTeam.hpp"
#include "CFont.hpp"
#include "CPilot.hpp"
#include "CFollowFactory.hpp"
#include "CFollowBluePrint.hpp"
#include "CSpriteObjs.hpp"


CFollowSpecial::CFollowSpecial(const CShipBluePrint &shipBluePrint,
                               CShip &ship, CLevel &level):
    CSpecial(shipBluePrint, ship, level,
             shipBluePrint.mFollowSpecBluePrint->mSound,
             shipBluePrint.mFollowSpecBluePrint->mStatSprite),
    mBluePrint(*shipBluePrint.mFollowSpecBluePrint),
    mSprites(mBluePrint.GetSprites()),
    mFollower(0) {


}

const CGravSprite& CFollowSpecial::GetSprite() const {
    return *((mBluePrint.GetSprites())[0]);
}


CMoverObj* CFollowSpecial::UseAt(const CVector2& pos, const CVector2& vel,
                                 const std::string& name, bool shadow) {

    if(!mFollower) {
        CSound * const sound = 0;
        const CVector2 offset(0, 0);
        CFollowFactory& factory = CFollowFactory::Instance();
        mFollower = factory.CreateObject(name, mBluePrint.GetSprites(),
                                         mLevel, mShip, sound, offset);
        PlaySound();
    }

    return mFollower;
}


void CFollowSpecial::NotUsing() {
    if(mFollower && CSpriteObjs::HasObj(mFollower) &&
       dynamic_cast<CFollower*>(mFollower))
        mFollower->Die();
    mFollower = nullptr;
}


bool CFollowSpecial::IsActive() const {
    return mFollower ? mFollower->IsActive() : false;
}


float CFollowSpecial::GetDepletionScale(float dt) const {
    return 50*dt;
}
