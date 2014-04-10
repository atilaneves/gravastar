#include "CExplosive.hpp"
#include "CGravSprite.hpp"
#include "CLevel.hpp"
#include "CSpriteObjs.hpp"
#include "CExplosiveBluePrint.hpp"
#include "CExplosion.hpp"
#include "CShips.hpp"



CExplosive::CExplosive(const CExplosiveBluePrint &bluePrint, CLevel &level,
                       CPilot& pilot,
                       const CVector2 &pos, const CVector2 &vel,
                       float maxHull):
    CMoverObj(bluePrint.GetSprites(), level, pos, vel),
    mHull(maxHull), mMaxHull(maxHull), mPilot(pilot),
    mExpSprites(bluePrint.GetExplosionSprites()),
    mExpSound(*bluePrint.mSound) {

}


void CExplosive::Update(float dt) {
    CMoverObj::Update(dt);
    CheckCollision(dt);
}


void CExplosive::LoseHull(float amount) {
    mHull -= amount;
    if(mHull > mMaxHull) mHull = mMaxHull;
    if(!IsActive()) AtDeath();
}


void CExplosive::AtDeath() {

    Erase();
    mHull = -1; //guarantees it's not active
    CSpriteObj *hitObj = GetHitObj();
    if(hitObj) mPos = hitObj->GetPos();
    new CExplosion(mLevel, mPos, mExpSprites, mExpSound);

    if(mShockWaveForce > 0 && mMass > 0) {//don't bother if we don't push anyone
        float force = mShockWaveForce * sqrt(mMass); //bigger pushes more
        CShips::PushAll(mPos, force, hitObj, mPilot);
    }
}
